//****************************************************************************//
//**                                                                        **//
//** File:         vmcore.hpp                                               **//
//** Description:  Virtual Machine Core definitions                         **//
//** Comment(s):   Internal developer version only                          **//
//** Library:                                                               **//
//** Created:      2001-08-29                                               **//
//** Author(s):    Karl Churchill                                           **//
//** Note(s):                                                               **//
//** Copyright:    (C)1996 - , eXtropia Studios                             **//
//**               All Rights Reserved.                                     **//
//**                                                                        **//
//****************************************************************************//

#ifndef _VM_CORE_HPP_
#define _VM_CORE_HPP_
#include "vm.hpp"
#include "vm_targetmacros.hpp"

#if _VM_INTERPRETER == _VM_INTERPRETER_FUNC_TABLE
  #define _DECLARE_OP(x)  static void do##x(VMCore*, uint16);
  #define _DEFINE_OP(x)   void VMCore::do##x(VMCore* vm, uint16 op)
  #define _REFER_OP(x)    VMCore::do##x
  #define _END_OP
  #define _THROW(x) return;
#elif _VM_INTERPRETER == _VM_INTERPRETER_SWITCH_CASE
  #define _DECLARE_OP(x)
  #define _DEFINE_OP(x)   case VMDefs::_##x:
  #define _END_OP         break;
  #define _REFER_OP(x)
  #define _THROW(x)       return ++numStatements; // not forgetting the one just executed!
#elif _VM_INTERPRETER == _VM_INTERPRETER_CUSTOM
/*
  #define _DECLARE_OP(x)
  #define _DEFINE_OP(x)
  #define _END_OP
  #define _REFER_OP(x)
  #define _THROW(x)
*/
#else
  #error No interpreter model set
#endif



class VMCore {
  public:
    typedef void (*Native)(VMCore* vm);
    union GPR { // General Purpose 64-bit register type
      friend class VMCore;
      private:  // Data arrangement
        union { uint8     _u8[8];   sint8     _s8[8];                                       };
        union { uint16    _u16[4];  sint16    _s16[4];                                      };
        union { uint32    _u32[2];  sint32    _s32[2];  float32 _f32[2];                    };
        union { uint64    _u64;     sint64    _s64;     float64 _f64;                       };
        #if X_PTRSIZE == XA_PTRSIZE64
        // 64-bit pointers
        union { uint8*    _pu8;     uint16*   _pu16;    uint32* _pu32;    uint64* _pu64;    };
        union { sint8*    _ps8;     sint16*   _ps16;    sint32* _ps32;    sint64* _ps64;    };
        union { float32*  _pf32;    float64*  _pf64;                                        };
        union { char*     _pch;     wchar_t*  _pwch;                                        };
        #else
        union { uint8*    _pu8[2];  uint16*   _pu16[2]; uint32* _pu32[2]; uint64* _pu64[2]; };
        union { sint8*    _ps8[2];  sint16*   _ps16[2]; sint32* _ps32[2]; sint64* _ps64[2]; };
        union { float32*  _pf32[2]; float64*  _pf64[2];                                     };
        union { char*     _pch[2];  wchar_t*  _pwch[2];                                     };
        #endif
      public:
        // obtain pointer to actual register operand
        void*     data8();
        void*     data16();
        void*     data32();
        void*     data64();
        void*     data(uint32 s);

        // obtain pointer interpretation of register operand
        char*     &pCh();
        uint8*    &pU8();
        uint16*   &pU16();
        uint32*   &pU32();
        uint64*   &pU64();
        sint8*    &pS8();
        sint16*   &pS16();
        sint32*   &pS32();
        sint64*   &pS64();
        float32*  &pF32();
        float64*  &pF64();

        // obtain reference to actual register operand (for direct reading/writing)
        uint8&    u8();
        uint16&   u16();
        uint32&   u32();
        uint64&   u64();
        sint8&    s8();
        sint16&   s16();
        sint32&   s32();
        sint64&   s64();
        float32&  f32();
        float64&  f64();

        // obtain 32-bit register halves
        uint32&   getMSW();
        uint32&   getLSW();
    };

  private:
    GPR       gpr[16];    // register set

    union {
      const uint16*         inst;   // normal interpretation
      const uint8*          extU8;
      const uint16*         extU16;
      const uint32*         extU32;
      const uint64*         extU64;
      const sint8*          extS8;
      const sint16*         extS16;
      const sint32*         extS32;
      const sint64*         extS64;
      const uint16* const * extCodeAddr;
      const Native* const * extNativeCodeAddr;
    } pc;         // program counter

    uint16**  callStack;  // return address stack
    uint64*   regStack;   // register save/restore stack
    union {
      uint8*  u8;
      uint16* u16;
      uint32* u32;
      uint64* u64;
    } dataStack;  // general data stack

    uint16**  callStackBase;
    uint64*   regStackBase;
    uint8*    dataStackBase;

    uint16**  callStackTop;
    uint64*   regStackTop;
    uint8*    dataStackTop;

    uint32    status;

    size_t    regStackSize;
    size_t    dataStackSize;
    size_t    callStackSize;

    #if _VM_INTERPRETER == _VM_INTERPRETER_FUNC_TABLE
      #include "vm_handlers.hpp"
    #endif
    static const char* statusCodes[];


    #if X_PTRSIZE == XA_PTRSIZE32
    static const uint16* getPCFor32BitHost(VMCore* vm)
    {
      const uint16* result = vm->pc.extCodeAddr[EX_ADDR_32];
      vm->pc.extU64++;
      return result;
    }

    static const VMCore::Native* getNativeFor32BitHost(VMCore* vm)
    {
      const VMCore::Native* result = vm->pc.extNativeCodeAddr[EX_ADDR_32];
      vm->pc.extU64++;
      return result;
    }
    #endif

  public:
    enum {
      DEF_REG_STACK   = 1024,
      DEF_DATA_STACK  = 4096,
      DEF_CALL_STACK  = 4096
    };
    VMCore(size_t rStackSize = DEF_REG_STACK, size_t dStackSize = DEF_DATA_STACK, size_t cStackSize = DEF_CALL_STACK);
    ~VMCore();

    uint32  getStatus() { return status; }

  public:
    GPR&    getReg(sint32 i) { return gpr[(i&0xF)]; }
    void    dump();
    void    setPC(uint16* newPC) { pc.inst = newPC; }
    void    execute();

    #if _VM_INTERPRETER == _VM_INTERPRETER_SWITCH_CASE
  private:
    int    innerExecute();
    #endif
};

#endif
