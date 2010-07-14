#include "timer.hpp"

#ifdef WIN32
#include <windows.h>
#else
#include <sys/time.h>
#endif

float Timer::getSeconds() const
{
	return getTime()-m_start_time;
}

void Timer::reset()
{
	m_start_time=getTime();
}

Timer::Timer():
	m_start_time(0.0)
{
#ifdef WIN32
	LARGE_INTEGER frequency;

	if(!QueryPerformanceFrequency(&frequency))
		throw TimerException("Timer::Timer(): QueryPerformanceFrequency() failed");
	
	m_frequency=frequency.QuadPart;
#else
	if(clock_getres(CLOCK_MONOTONIC,0) == -1)
		throw TimerException("Timer::Timer(): clock_getres() failed");
#endif

	m_start_time=getTime();
}

float Timer::getTime() const
{
	//TODO: implement support for more precise timers
	//TODO: handle rollovers

#ifdef WIN32	
	LARGE_INTEGER time;
	
	if(!QueryPerformanceCounter(&time))
		throw TimerException("Timer::getTime(): QueryPerformanceCounter failed");

	return float(time.QuadPart)/m_frequency;
#else
	timespec time;

	if(clock_gettime(CLOCK_MONOTONIC,&time) == -1)
		throw TimerException("Timer::getTime(): QueryPerformanceCounter failed");
	
	return time.tv_sec+float(t.tv_nsec)/1000000000.0;
#endif	
}
