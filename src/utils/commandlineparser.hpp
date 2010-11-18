#ifndef COMMANDLINEPARSER_HPP
#define COMMANDLINEPARSER_HPP

#include <string>
#include <iostream>
#include <sstream>
#include <fstream>
#include <cstdlib>
#include <map>
#include <stdexcept>

class CommandLineParseError: public std::runtime_error
{
	public:
		CommandLineParseError(const std::string& msg):
			std::runtime_error(msg)
		{
		
		}
};

class CommandLineParser
{
	public:
		template<typename T>
		bool getValue(const std::string& key,T& value);
		bool getValue(const std::string& key,std::string& value);
		
		CommandLineParser(int argc,char** argv);
				
	private:
		void parse(int argc,char** argv);
	
		std::map<std::string,std::string> values;

};

template<typename T>
bool CommandLineParser::getValue(const std::string& key,T& value)
{
	if(values.find(key) == values.end())
	{
		return false;
	}

	T temp;
	
	std::stringstream ss;
	ss << values[key];
	
	ss >> temp;
	
	if (ss.fail())
		return false;
		
	value = temp;
	return true;
}

#endif // COMMANDLINEPARSER_HPP

