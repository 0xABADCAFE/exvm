//****************************************************************************//
//**                                                                        **//
//** File:         machine_amiga_os4.hpp                                    **//
//** Description:  Host Machine definitions for AmigaOS4 PowerPC            **//
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
#include <proto/exec.h>
#include <proto/timer.h>

namespace ExVM {

  class MilliClock {
    private:
      static uint32 clockFreq;
      EClockVal     mark;

    public:
      void      set()     {
        ITimer->ReadEClock(&mark);
      }
      uint32    elapsed();
      float64   elapsedFrac();

    public:
      MilliClock();
  };

}

