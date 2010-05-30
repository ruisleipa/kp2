#ifndef __INIFILE_HPP
#define __INIFILE_HPP

#include <string>
#include <iostream>
#include <sstream>
#include <fstream>
#include <map>
#include <cstdlib>
#include <vector>


class IniFile
{
	public:
		//	Takes a pointer to the variable to put the value, and a keyword. Returns true, if the variable value was found, false otherwise.
		template<typename vtype>
		bool getValue(vtype&,const std::string&);
		bool getValue(std::string&,const std::string&);
		template<typename vtype>
		bool getValue(std::vector<vtype>&, const std::string&);
			
		//	Takes a variable=value pair, first parameter is the variable name aka. the keyword, second is the value. Returns true 
		template<typename vtype>
		bool setValue(const std::string&,const vtype&);
		bool setValue(const std::string&,const std::string&);
		template<typename vtype>
		bool setValue(const std::string&,const std::vector<vtype>&);
		
		int load(std::string filename);
		int save(std::string filename);

		IniFile(std::string filename);
				
	private:
		std::map<std::string,std::string> m_values;
	
};

template<typename vtype>
bool IniFile::setValue(const std::string& key,const vtype& value)
{

	std::string str;
	std::stringstream ss;
	ss << value;
	ss >> str;
	
	if (ss.fail())
	return false;
	
	m_values[key] = str;
	
	return true;
};

template<typename vtype>
bool IniFile::getValue(vtype& var,const std::string& key)
{
	if(m_values.find(key) == m_values.end())
		return false;
	vtype temp;
	
	std::stringstream ss;
	ss << m_values[key];
	
	ss >> temp;
	
	if (ss.fail())
		return false;
		
	var = temp;
	return true;
}

template<typename vtype>
bool IniFile::setValue(const std::string& key,const std::vector<vtype>& value)
{
	std::string element;

	for (int i=0;i<value.size(); i++)
	{
		//convert vtype to string
		std::string str;
		std::stringstream ss;
		ss << value.at(i);
		ss >> str;
		
		if (ss.fail())
			return false;
			
		element += str + ';';
	}

	m_values[key] = element;
	
	return true;
}

template<typename vtype>
bool IniFile::getValue(std::vector<vtype>& var, const std::string& key)
{
	var.clear();
	
	if(m_values.find(key) == m_values.end())
		return false;

	std::string raw_value;
	raw_value = m_values[key];

	//If there isn't anything, then we'll just return false.
	if ((raw_value.find(';') == std::string::npos) && (raw_value.size()<1))
		return false;

	size_t search_pos = 0, old_pos = 0;
	while (old_pos != std::string::npos)
	{
		//We need to skip ;-chars, but there aren't one in beginning.
		if (old_pos == 0)
			search_pos = raw_value.find(';');
		else
			search_pos = raw_value.find(';', old_pos+1);

		std::string element;
		//This will most likely to return an empty element, it happens
		//when there is final ;-char. e.g (value1;value2;)
		if (search_pos == std::string::npos)
			element = raw_value.substr(old_pos+1);
		//Again, we need this because of those nasty ;-chars.
		else if (old_pos == 0)
			element = raw_value.substr(0, search_pos);
		else
			element = raw_value.substr(old_pos+1, search_pos-old_pos-1);

		if (element.size() > 0)
		{
			vtype value;
			std::stringstream ss;
			ss << element;
			ss >> value;
			if (ss.fail())
				return false;
	
			var.push_back(value);
		}
		old_pos = search_pos;
	}

	return true;	
}

#endif // __INIFILE_HPP
