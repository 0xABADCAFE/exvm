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
  #define _VM_HOST_HAIKU_X64        8
  #define _VM_HOST_HAIKU_X86        9
  #define _VM_HOST_MACOS_X64        10


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

    // Formatting Templates
    #define FS16 "hd"
    #define FU16 "hu"
    #define FS32 "d"
    #define FU32 "u"
    #define FS64 "ld"
    #define FU64 "lu"
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

    // Formatting Templates
    #define FS16 "hd"
    #define FU16 "hu"
    #define FS32 "ld"
    #define FU32 "lu"
    #define FS64 "lld"
    #define FU64 "llu"
  #endif

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
    #include "platforms/machine_linux_generic.hpp"
  #elif _VM_HOST_OS == _VM_HOST_WIN32_I386
    #warning This target is almost certainly not working
    #include "platforms/machine_win32.hpp"
  #elif (_VM_HOST_OS == _VM_HOST_AMIGAOS3_68K)
    #include "platforms/machine_amiga_68k.hpp"
  #elif (_VM_HOST_OS == _VM_HOST_AMIGAOS3_WARPUP)
    #include "platforms/machine_amiga_wos.hpp"
  #elif (_VM_HOST_OS == _VM_HOST_AMIGAOS4_PPC)
    #include "platforms/machine_amiga_os4.hpp"
  #elif (_VM_HOST_OS == _VM_HOST_MORPHOS_PPC)
    #include "platforms/machine_amiga_mos.hpp"
  #elif (_VM_HOST_OS == _VM_HOST_HAIKU_X64)
    #define X_ENDIAN XA_LITTLEENDIAN
    #include "platforms/machine_haiku_generic.hpp"
  #elif (_VM_HOST_OS == _VM_HOST_HAIKU_X86)
    #define X_ENDIAN XA_LITTLEENDIAN
    #include "platforms/machine_haiku_generic.hpp"
  #elif (_VM_HOST_OS == _VM_HOST_MACOS_X64)
    #define X_ENDIAN XA_LITTLEENDIAN
    #include "platforms/machine_macos_generic.hpp"

#else
    #error Unrecognised Machine
  #endif

#endif

