#ifndef _TIMER_HPP
#define _TIMER_HPP

#ifdef WIN32
#include <windows.h>
#elif USE_SDL_GETTICKS
#include <SDL/SDL.h>
#else
#include <sys/time.h>
#endif

class timer
{
	public:
		timer()
		{
			#ifdef WIN32
				BOOL retval;
				LARGE_INTEGER f;
				retval = QueryPerformanceFrequency(&f);
				if (retval)
				{
					frequency = f.QuadPart;
					#ifdef DEBUG_MODE
					std::cout << "Using QueryPerformanceCounter()\n";
					std::cout << "Timer frequency: " << (f.QuadPart * 0.000001) << " MHz\n";
					#endif
				}
				else
				{
					#ifdef DEBUG_MODE
					std::cerr << "QueryPerformanceCounter() failed\n";
					#endif
					abort();
				}
			#elif USE_SDL_GETTICKS
				#ifdef DEBUG_MODE
				std::cout << "Using SDL_GetTicks()\n";
				std::cout << "Timer frequency: " << (1000 * 0.000001) << " MHz\n";
				#endif
			#else
				int retval;
				retval = clock_getres(CLOCK_REALTIME, &frequency);
				if (retval)
				{
					#ifdef DEBUG_MODE
					std::cerr << "clock_getres(CLOCK_REALTIME) failed\n";
					#endif
					abort();
				}
				else
				{
					#ifdef DEBUG_MODE
					std::cout << "Using clock_getres(CLOCK_REALTIME)\n";
					std::cout << "Timer frequency: " << (frequency.tv_sec + double (frequency.tv_nsec) / 1000000000.0) * 0.000001 << " MHz\n";
					#endif
				}
			#endif
		}
		double get_seconds()
		{
			// RETURN SECONDS!!
			#if WIN32
				QueryPerformanceCounter(&t);
				return double(t.QuadPart) / frequency;
			#elif USE_SDL_GETTICKS
				return double (SDL_GetTicks()) * 0.001;
			#else
				int retval = clock_gettime(CLOCK_REALTIME, &t);
				if (retval)
				{
					std::cerr << "clock_gettime() returned " << retval << "\n";
					abort();
				}
				return t.tv_sec + double (t.tv_nsec) / 1000000000.0;
			#endif
			
		}
		
		double get_ticks()
		{
			abort();
			return 0.0;
		}
	private:
		#ifdef WIN32
		double frequency;
		LARGE_INTEGER t;
		#else
		timespec frequency, t;
		#endif
		
};

#endif
