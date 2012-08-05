#ifndef EXCEPTION_EXCEPTION_HPP
#define EXCEPTION_EXCEPTION_HPP

#include <string>

class Exception
{
	public:
		Exception(const std::string& msg);

		const std::string getMessage();

	private:
		std::string msg;

};

#endif
