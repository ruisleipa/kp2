#ifndef EXCEPTION_HPP
#define EXCEPTION_HPP

#include "stacktrace.hpp"

#include <stdexcept>

class Exception: public std::runtime_error
{
	public:
		Exception(const std::string& what);:
			std::runtime_error(what)
		{
			
		}
		
		friend std::ostream& operator<<(std::ostream& os,const Exception& e);
};

#endif // EXCEPTION_HPP
