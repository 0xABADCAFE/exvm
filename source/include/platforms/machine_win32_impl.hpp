//****************************************************************************//
//**                                                                        **//
//** File:         machine_win32_impl.hpp                                   **//
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
  uint32 current = GetTickCount();
  return current - mark;
}

float64 MilliClock::elapsedFrac() {
  return (float64)elapsed();
}

