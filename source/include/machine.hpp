//****************************************************************************//
//**                                                                        **//
//** File:         machine.hpp                                              **//
//** Description:  Host Machine definitions                                 **//
//** Comment(s):   Internal developer version only                          **//
//** Library:                                                               **//
//** Created:      2001-08-29                                               **//
//** Author(s):    Karl Churchill                                           **//
//** Note(s):      Stub replacement for needed exng/xbase.hpp defs          **//
//** Copyright:    (C)1996 - , eXtropia Studios                             **//
//**               All Rights Reserved.                                     **//
//**                                                                        **//
//****************************************************************************//

#ifndef _VM_HOST_MACHINE_HPP_
#define _VM_HOST_MACHINE_HPP_
#include <cstdlib>

// this is just a gap filler for framework xbase definitions

/*
Type


Format string

int %d
long %ld
long long %lld
size_t %zd
ptrdiff_t %td
any pointer %p

*/

#define XA_BIGENDIAN 0
#define XA_LITTLEENDIAN 1
#define XA_PTRSIZE32 32
#define XA_PTRSIZE64 64

// change this for other systems
#define _VM_HOST_AMIGAOS3_68K     1
#define _VM_HOST_AMIGAOS3_WARPUP  2
#define _VM_HOST_LINUX_I386       3
#define _VM_HOST_WIN32_I386       4
#define _VM_HOST_LINUX_X64        5
#define _VM_HOST_AMIGAOS4_PPC     6
#define _VM_HOST_MORPHOS_PPC      7


#define _VM_INTERPRETER_FUNC_TABLE     1
#define _VM_INTERPRETER_SWITCH_CASE    2
#define _VM_INTERPRETER_CUSTOM_ASM     3

#ifdef __LP64__
  #define X_PTRSIZE XA_PTRSIZE64
typedef signed char sint8;
typedef signed short int sint16;
typedef signed int sint32;
typedef signed long int sint64;
typedef unsigned char uint8;
typedef unsigned short int uint16;
typedef unsigned int uint32;
typedef unsigned long int uint64;
typedef float float32;
typedef double float64;
#else
  #define X_PTRSIZE XA_PTRSIZE32
typedef signed char sint8;
typedef signed short int sint16;
typedef signed long int sint32;
typedef signed long long int sint64;
typedef unsigned char uint8;
typedef unsigned short int uint16;
typedef unsigned long int uint32;
typedef unsigned long long int uint64;
typedef float float32;
typedef double float64;
#endif

#define rsint8 register sint8
#define rsint16 register sint16
#define rsint32 register sint32
#define rsint64 register sint64
#define ruint8 register uint8
#define ruint16 register uint16
#define ruint32 register uint32
#define ruint64 register uint64
#define rfloat32 register float32
#define rfloat64 register float64

// Target sanity checks

#if (_VM_HOST_OS == _VM_HOST_AMIGAOS3_68K)
  #ifdef __PPC__
    #warning PowerPC directive set for AmigaOS 680x0 target, switching to WarpOS
    #undef _VM_HOST_OS
    #define _VM_HOST_OS _VM_HOST_AMIGAOS3_WARPUP
  #endif
#endif

#if (_VM_HOST_OS == _VM_HOST_AMIGAOS3_WARPUP) || (_VM_HOST_OS == _VM_HOST_AMIGAOS3_68K)
  #ifdef __LP64__
    #error 64-bit directive set for AmigaOS 3.x target, no known supported 64-bit architecture
  #endif
#endif

#if (_VM_HOST_OS == _VM_HOST_LINUX_I386)
  #ifdef __LP64__
    #warning 64-bit directive set for Linux i386 target, switching to x64
    #undef _VM_HOST_OS
    #define _VM_HOST_OS _VM_HOST_LINUX_X64
  #endif
#endif

// target specific class implementations

#if (_VM_HOST_OS == _VM_HOST_LINUX_I386) || (_VM_HOST_OS == _VM_HOST_LINUX_X64)
  #define X_ENDIAN XA_LITTLEENDIAN
  #include <sys/time.h>
  #include <time.h>

class MilliClock {
  friend class Clock;
  private:
    static struct timezone  tz;
    timeval mark;

  public:
    void      set()     { gettimeofday(&mark, &tz); }
    uint32    elapsed();
    float64   elapsedFrac();

  public:
    MilliClock() { set(); }
};

#elif _VM_HOST_OS == _VM_HOST_WIN32_I386
  #define X_ENDIAN XA_LITTLEENDIAN
  #include <windows.h>

class MilliClock {
  private:
    uint32 mark;

  public:
    void      set()     { mark = GetTickCount(); }
    uint32    elapsed();
    float64   elapsedFrac();

  public:
    MilliClock() { set(); }
};

#elif (_VM_HOST_OS == _VM_HOST_AMIGAOS3_68K)
  #define X_ENDIAN XA_BIGENDIAN
  #include <proto/timer.h>

class MilliClock {
  private:
    static uint32 clockFreq;
    EClockVal     mark;

  public:
    void      set()     { ::ReadEClock(&mark); }
    uint32    elapsed();
    float64   elapsedFrac();

  public:
    MilliClock() { clockFreq = ::ReadEClock(&mark); }
};

#elif (_VM_HOST_OS == _VM_HOST_AMIGAOS3_WARPUP)
  #define X_ENDIAN XA_BIGENDIAN
  #include <proto/exec.h>
  #include <devices/timer.h>
  #include <proto/powerpc.h>

class MilliClock {
  private:
    timeval   mark;

  public:
    void      set()     { ::GetSysTimePPC(&mark); }
    uint32    elapsed();
    float64   elapsedFrac();

  public:
    MilliClock() { set(); }
};

#elif (_VM_HOST_OS == _VM_HOST_AMIGAOS4_PPC)
  #define X_ENDIAN XA_BIGENDIAN
  #include <proto/exec.h>
  #include <proto/timer.h>

class MilliClock {
  private:
    static uint32 clockFreq;
    EClockVal     mark;

  public:
    void      set()     { ITimer->ReadEClock(&mark); }
    uint32    elapsed();
    float64   elapsedFrac();

  public:
    MilliClock();
};


#else
  #error Unrecognised Machine
#endif

#endif
