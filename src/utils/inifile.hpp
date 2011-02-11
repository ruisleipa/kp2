#ifndef INIFILE_HPP
#define INIFILE_HPP

#include <string>
#include <sstream>
#include <map>
#include <stdexcept>
#include <typeinfo>

#include "utils/demangle.hpp"

class IniFile
{
	public:
		template<typename T>
		void getValue(const std::string& key,T& value);
		void getValue(const std::string& key,std::string& value);
			
		template<typename T>
		void setValue(const std::string& key,const T& value);
		void setValue(const std::string& key,const std::string& value);
		
		void load(const std::string& filename);
		void save(const std::string& filename);

		IniFile();
		IniFile(const std::string& filename);
				
	private:
		std::map<std::string,std::string> values;
		
		std::string filename;
	
};

template<typename T>
void IniFile::setValue(const std::string& key,const T& value)
{
	std::ostringstream ss;
	ss << value;
	
	if (ss.fail())
	{
		std::stringstream ss;
		
		ss << "Given value '" << value << "' for key '" << key << " cannot be converted to string.";
		
		throw std::runtime_error(ss.str());
	}
	
	values[key] = ss.str();
};

template<typename T>
void IniFile::getValue(const std::string& key,T& value)
{
	if(values.find(key) == values.end())
	{
		std::stringstream ss;
	
		ss << "Key \"" << key;
		ss << "\" not found in file loaded from \"";
		ss << filename << "\"";
			
		throw std::runtime_error(ss.str());
	}
		
	T temp;
	
	std::stringstream ss;
	ss << values[key];
	
	ss >> temp;
	
	if (ss.fail())
	{
		std::stringstream ss;
	
		ss << "Key \"" << key;
		ss << "\" does not match type \"";
		ss << demangleName(typeid(value).name()) << "\".";
			
		throw std::runtime_error(ss.str());
	}
		
	value = temp;
}

#endif // INIFILE_HPP

