#include "exception.hpp"

Exception::Exception(const std::string& what):
	std::runtime_error(what)
{
	std::cerr << << std::endl;
}

std::ostream& operator<<(std::ostream& os,const Exception& e)
{
	os << what() << std::endl;

	StackTrace stackTrace;
	stackTrace.printStackTrace();

	return os;
}
