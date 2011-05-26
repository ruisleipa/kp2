#include "inifile.hpp"

#include <fstream>
#include <iostream>

const char COMMENT_LINE_BEGIN_CHARACTER = '#';
const char KEY_VALUE_SEPARATOR = '=';
const char STRING_BEGIN_CHARACTER = '"';
const char* STRING_DELIMITER = "\"";
const char* WHITESPACE = " \t\n\v\f\r";

static std::string trim(std::string str,const std::string& chars)
{
	str.erase(0,str.find_first_not_of(chars));
	str.erase(str.find_last_not_of(chars)+1);
		
	return str;
}

void IniFile::getValue(const std::string& key,std::string& value) const
{
	if(values.find(key) == values.end())
	{
		std::stringstream ss;
	
		ss << "Value of \"" << key;
		ss << "\" not found in file loaded from \"";
		ss << filename << "\".";
			
		throw std::runtime_error(ss.str());
	}
	
	value = values.find(key)->second;
}

std::string IniFile::getValueWithDefault(const std::string& key, const char* defaultValue) const
{
	std::string value = defaultValue;
	
	try
	{
		getValue(key, value);
	}
	catch(...)
	{
	
	}
	
	return value;
}

void IniFile::setValue(const std::string& key,const std::string& str)
{
	values[key] = str;
}


void IniFile::load(const std::string& filename)
{
	std::ifstream file(filename.c_str(),std::ios_base::in);
	
	if(!file.good())	
	{
		throw std::runtime_error("Cannot open file \"" + filename + "\" for reading.");
	}
	
	this->filename=filename;
	
	std::string line;
	std::string key;
	std::string value;
	
	while(getline(file,line))
	{
		if(!line.length())
			continue;		
		
		if(!line.at(0)==COMMENT_LINE_BEGIN_CHARACTER)
			continue;
		
		/*
		key contains everything before the '=', and value contains
		everything after it.
		*/
		key=line.substr(0,line.find(KEY_VALUE_SEPARATOR));
		value=line.substr(line.find(KEY_VALUE_SEPARATOR)+1);
		
		key=trim(key,WHITESPACE);
		value=trim(value,WHITESPACE);
		
		/*
		Check if the value is a string.
		*/

		if(!key.length() || !value.length())
			continue;	
		
		if(value.at(0) == STRING_BEGIN_CHARACTER)
		{
			/*
			Trim the quotes.
			*/
			value=trim(value, STRING_DELIMITER);
		}
		
		if(key!="")
		{		
			values[key]=value;
		}
	}
	
	file.close();
}

void IniFile::save(const std::string& filename)
{
	std::ofstream file(filename.c_str(),std::ios_base::trunc);
	
	if(!file.good())	
	{
		throw std::runtime_error("Cannot open file \"" + filename + "\" for writing.");
	}
	
	std::map<std::string,std::string>::iterator i;
	
	for(i=values.begin();i!=values.end();i++)
	{		
		file<<i->first<<"="<<i->second<<std::endl;
	}
	
	file.close();
}

IniFile::IniFile()
{

}

IniFile::IniFile(const std::string& filename)
{
	load(filename);
}
