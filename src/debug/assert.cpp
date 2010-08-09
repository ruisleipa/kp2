#include "assert.hpp"

#include <iostream>

void _assert(const char* e,const char* file,int line)
{
	std::cerr<<"assertion failed: ";
	std::cerr<<file<<":"<<line<<": ";
	std::cerr<<e<<std::endl;
	
}
