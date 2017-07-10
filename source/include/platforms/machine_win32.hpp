//****************************************************************************//
//**                                                                        **//
//** File:         machine_win32.hpp                                        **//
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

#define X_ENDIAN XA_LITTLEENDIAN
#include <windows.h>

class MilliClock {
  private:
    uint32 mark;

  public:
    void      set(){
      mark = GetTickCount();
    }
    uint32    elapsed();
    float64   elapsedFrac();

  public:
    MilliClock() {
      set();
    }
};

