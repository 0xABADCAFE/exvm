//****************************************************************************//
//**                                                                        **//
//** File:         machine_amiga_wos.hpp                                    **//
//** Description:  Host Machine definitions for AmigaOS 3.x/WUP PowerPC     **//
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
#include <devices/timer.h>
#include <proto/powerpc.h>

namespace ExVM {

  class MilliClock {
    private:
      timeval   mark;

    public:
      void      set() {
        ::GetSysTimePPC(&mark);
      }
      uint32    elapsed();
      float64   elapsedFrac();

    public:
      MilliClock() {
        set();
      }
  };

}

