//****************************************************************************//
//**                                                                        **//
//** File:         machine_haiku_generic_impl.hpp                           **//
//** Description:  Host Machine implementation for generic haiku            **//
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

struct timezone MilliClock::tz = { 0 };

uint32 MilliClock::elapsed() {
  timeval current;
  gettimeofday(&current, &tz);
  if (current.tv_sec == mark.tv_sec) {
    return (current.tv_usec - mark.tv_usec)/1000;
  }
  return (1000 * (current.tv_sec - mark.tv_sec)) + ((current.tv_usec - mark.tv_usec) / 1000);
}

float64 MilliClock::elapsedFrac() {
  timeval current;
  gettimeofday(&current, &tz);
  if (current.tv_sec == mark.tv_sec) {
    return 0.001 * (current.tv_usec - mark.tv_usec);
  }
  return (1000.0 * (current.tv_sec - mark.tv_sec)) + (0.001 * (current.tv_usec - mark.tv_usec));
}

