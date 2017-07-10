//****************************************************************************//
//**                                                                        **//
//** File:         machine_linux_amiga_wos_impl.hpp                         **//
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

////////////////////////////////////////////////////////////////////////////////
//
//  MilliClock
//
////////////////////////////////////////////////////////////////////////////////

uint32 MilliClock::elapsed() {
  timeval current;
  GetSysTimePPC(&current);
  SubTimePPC(&current, &mark);
  return (1000 * current.tv_secs) + (current.tv_micro / 1000);
}

float64 MilliClock::elapsedFrac() {
  timeval current;
  GetSysTimePPC(&current);
  SubTimePPC(&current, &mark);
  return (1000.0 * current.tv_secs) + (0.001 * (float64)current.tv_micro);
}

