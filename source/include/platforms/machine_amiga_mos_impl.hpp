//****************************************************************************//
//**                                                                        **//
//** File:         machine_amiga_mos.hpp                                    **//
//** Description:  Host Machine implementation for MorphOS PowerPC          **//
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

extern Device* TimerBase;

uint32 MilliClock::clockFreq = 0;

uint32 MilliClock::elapsed() {
  EClockVal current;
  ReadEClock(&current);
  ruint32 ticks;
  if (current.ev_hi == mark.ev_hi) {
    ticks = current.ev_lo - mark.ev_lo;
  }
  else {
    ticks = 0xFFFFFFFF - mark.ev_lo + current.ev_lo;
  }
  return (1000 * ticks) / clockFreq;
}

float64 MilliClock::elapsedFrac() {
  EClockVal current;
  ReadEClock(&current);
  float64 ticks;
  static float64 cF = 1000.0 / (float64)clockFreq;
  if (current.ev_hi == mark.ev_hi) {
    ticks = (current.ev_lo - mark.ev_lo);
  }
  else {
    ticks = (0xFFFFFFFF - mark.ev_lo + current.ev_lo);
  }
  return (cF * ticks);
}

