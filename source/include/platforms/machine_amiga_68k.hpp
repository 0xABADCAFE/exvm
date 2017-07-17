//****************************************************************************//
//**                                                                        **//
//** File:         machine_amiga_68k.hpp                                    **//
//** Description:  Host Machine definitions for AmigaOS 3.x / 680x0         **//
//** Comment(s):   Internal developer version only                          **//
//** Library:                                                               **//
//** Created:      2001-08-29                                               **//
//** Author(s):    Karl Churchill                                           **//
//** Note(s):      Stub replacement for needed exng/xbase.hpp defs          **//
//** Copyright:    (C)1996 - , eXtropia Studios                             **//
//**               All Rights Reserved.                                     **//
//**                                                                        **//
//****************************************************************************//

#define X_ENDIAN XA_BIGENDIAN
#include <proto/timer.h>

namespace ExVM {

class MilliClock {
  private:
    static uint32 clockFreq;
    EClockVal     mark;

  public:
    void      set()     {
      ::ReadEClock(&mark);
    }
    uint32    elapsed();
    float64   elapsedFrac();

  public:
    MilliClock() {
      clockFreq = ::ReadEClock(&mark);
    }
};

}

