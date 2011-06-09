#ifndef STRING_HPP
#define STRING_HPP

#include <string>
#include <sstream>
#include <vector>

std::string convertToString(std::wstring str);
std::wstring convertToWideString(std::string str);
std::vector<std::string> tokenize(std::string str,std::string delim);

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

template <class B, class A>
inline B convertTo(const A& a)
{
	std::stringstream ss;
	ss << a;
	B b;
	ss >> b;
	
	return b;
}

#endif

