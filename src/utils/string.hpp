#ifndef STRING_HPP
#define STRING_HPP

#include <string>
#include <sstream>

std::string convertToString(std::wstring str);
std::wstring convertToWideString(std::string str);

template <class T>
inline std::string convertToString(const T& t)
{
	std::stringstream ss;
	ss<<t;
	return ss.str();
}

template <class T>
inline std::wstring convertToWideString(const T& t)
{
	std::wstringstream ss;
	ss<<t;
	return ss.str();
}

#endif

