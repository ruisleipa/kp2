#ifndef TIMER_HPP
#define TIMER_HPP

#include <stdexcept>

class TimerException: public std::runtime_error
{
	public:
		TimerException(const std::string& what):
			std::runtime_error(what)
		{
		
		}
};

class Timer
{
	public:
		double getSeconds() const;
		void reset();
		
		Timer();
		
	private:
		double getTime() const;
	
		double m_start_time;
		
#ifdef WIN32
		double m_frequency;
#endif
};

#endif // TIMER_HPP
