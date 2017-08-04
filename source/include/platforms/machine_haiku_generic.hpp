//****************************************************************************//
//**                                                                        **//
//** File:         machine_haiku_generic.hpp                                **//
//** Description:  Host Machine definitions for generic haiku               **//
//** Comment(s):   Internal developer version only                          **//
//** Library:                                                               **//
//** Created:      2001-08-29                                               **//
//** Author(s):    Karl Churchill                                           **//
//** Note(s):      Stub replacement for needed exng/xbase.hpp defs          **//
//** Copyright:    (C)1996 - , eXtropia Studios                             **//
//**               All Rights Reserved.                                     **//
//**                                                                        **//
//****************************************************************************//

////////////////////////////////////////////////////////////////////////////////
//
//  MilliClock
//
////////////////////////////////////////////////////////////////////////////////

#include <sys/time.h>
#include <time.h>

namespace ExVM {

  class MilliClock {
    friend class Clock;
    private:
      static struct timezone  tz;
      timeval mark;

    public:
      void      set() {
        gettimeofday(&mark, &tz);
      }
      uint32    elapsed();
      float64   elapsedFrac();

    public:
      MilliClock() {
        set();
      }
  };

}

