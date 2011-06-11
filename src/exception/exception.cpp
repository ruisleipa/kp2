#include "exception.hpp"

Exception::Exception(const std::string& msg):
	msg(msg)
{

}

const std::string Exception::getMessage()
{
	return msg;
}
