//****************************************************************************//
//**                                                                        **//
//** File:         machine.cpp                                              **//
//** Description:  Support class definitions                                **//
//** Comment(s):   Internal developer version only                          **//
//** Library:                                                               **//
//** Created:      2001-08-29                                               **//
//** Author(s):    Karl Churchill                                           **//
//** Note(s):                                                               **//
//** Copyright:    (C)1996 - , eXtropia Studios                             **//
//**               All Rights Reserved.                                     **//
//**                                                                        **//
//****************************************************************************//

#include "machine.hpp"

#if (_VM_HOST_OS == _VM_HOST_LINUX_I386) || (_VM_HOST_OS == _VM_HOST_LINUX_X64)

////////////////////////////////////////////////////////////////////////////////
//
//  MilliClock
//
////////////////////////////////////////////////////////////////////////////////

struct timezone MilliClock::tz = { 0 };

uint32 MilliClock::elapsed()
{
  timeval current;
  gettimeofday(&current, &tz);
  if (current.tv_sec == mark.tv_sec) {
    return (current.tv_usec - mark.tv_usec)/1000;
  }
  return (1000*(current.tv_sec - mark.tv_sec)) + ((current.tv_usec - mark.tv_usec)/1000);
}

float64 MilliClock::elapsedFrac()
{
  timeval current;
  gettimeofday(&current, &tz);
  if (current.tv_sec == mark.tv_sec) {
    return 0.001*(current.tv_usec - mark.tv_usec);
  }
  return (1000.0*(current.tv_sec - mark.tv_sec)) + (0.001*(current.tv_usec - mark.tv_usec));
}


////////////////////////////////////////////////////////////////////////////////


#elif _VM_HOST_OS == _VM_HOST_WIN32_I386

uint32 MilliClock::elapsed()
{
  uint32  current = GetTickCount();
  return current-mark;
}

float64 MilliClock::elapsedFrac()
{
  return (float64) elapsed();
}

#elif (_VM_HOST_OS == _VM_HOST_AMIGAOS3_68K)

extern  Device* TimerBase;

uint32  MilliClock::clockFreq = 0;

////////////////////////////////////////////////////////////////////////////////

uint32 MilliClock::elapsed()
{
  EClockVal current;
  ReadEClock(&current);
  ruint32 ticks;
  if (current.ev_hi == mark.ev_hi)
    ticks = current.ev_lo - mark.ev_lo;
  else
    ticks = 0xFFFFFFFF-mark.ev_lo + current.ev_lo;
  return (1000*ticks)/clockFreq;
}

float64 MilliClock::elapsedFrac()
{
  EClockVal current;
  ReadEClock(&current);
  float64 ticks;
  static float64 cF = 1000.0/(float64)clockFreq;
  if (current.ev_hi == mark.ev_hi)
    ticks = (current.ev_lo - mark.ev_lo);
  else
    ticks = (0xFFFFFFFF-mark.ev_lo + current.ev_lo);
  return (cF*ticks);
}

////////////////////////////////////////////////////////////////////////////////

#elif (_VM_HOST_OS == _VM_HOST_AMIGAOS3_WARPUP)

uint32 MilliClock::elapsed()
{
  timeval current;
  GetSysTimePPC(&current);
  SubTimePPC(&current, &mark);
  return (current.tv_secs*1000) + (current.tv_micro/1000);
}

float64 MilliClock::elapsedFrac()
{
  timeval current;
  GetSysTimePPC(&current);
  SubTimePPC(&current, &mark);
  return (1000.0*current.tv_secs) + (0.001*(float64)current.tv_micro);
}

#elif (_VM_HOST_OS == _VM_HOST_AMIGAOS4_PPC)

uint32  MilliClock::clockFreq = 0;

struct Device *TimerBase;
struct TimerIFace *ITimer;

MilliClock::MilliClock()
{
	if (!clockFreq) {
		TimerBase = (Device*)     IExec->FindName(&SysBase->DeviceList, "timer.device");
		ITimer    = (TimerIFace*) IExec->GetInterface((struct Library *)TimerBase, "main", 1, 0);
		clockFreq = ITimer->ReadEClock(&mark);
	}
}

uint32 MilliClock::elapsed()
{
  EClockVal current;
  ITimer->ReadEClock(&current);
  uint32 ticks;
  if (current.ev_hi == mark.ev_hi) {
    ticks = current.ev_lo - mark.ev_lo;
  }
  else {
    ticks = 0xFFFFFFFF-mark.ev_lo + current.ev_lo;
  }
  return (1000*ticks)/clockFreq;
}

float64 MilliClock::elapsedFrac()
{
  EClockVal current;
  ITimer->ReadEClock(&current);
  float64 ticks;
  static float64 cF = 1000.0/(float64)clockFreq;
  if (current.ev_hi == mark.ev_hi) {
    ticks = (current.ev_lo - mark.ev_lo);
  }
  else {
    ticks = (0xFFFFFFFF-mark.ev_lo + current.ev_lo);
  }
  return (cF*ticks);
}

#endif
