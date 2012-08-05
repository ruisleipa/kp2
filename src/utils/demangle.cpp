#include "demangle.hpp"

#include <cxxabi.h>
#include <cstdlib>

std::string demangleName(const char* name)
{
	char* demangledName=abi::__cxa_demangle(name,0,0,0);

	std::string result(demangledName);

	free(demangledName);

	return result;
}
