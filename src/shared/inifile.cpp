#include "inifile.hpp"

static std::string trim(const std::string& str,const std::string& chars="\t ")
{
	size_t begin=str.find_first_not_of(chars);
	size_t end=str.find_last_not_of(chars);
	
	if(begin == std::string::npos)
		begin = 0;

	if(end == std::string::npos)
		end = str.size()-1;
		
	return str.substr(begin,end-begin+1);
}

bool IniFile::getValue(const std::string& key,std::string& value)
{
	if(m_values.find(key) == m_values.end())
		return false;
	
	value=m_values[key];
	return true;
}

bool IniFile::setValue(const std::string& key,const std::string& str)
{
	m_values[key] = str;
	
	return true;
}


bool IniFile::load(const std::string& filename)
{
	std::ifstream file(filename.c_str(),std::ios_base::in);
	
	if(!file.good())	
	{
		std::cerr<<"Cannot open file "<<filename<<" for reading"<<std::endl;
		return false;
	}
	
	std::string line;
	std::string key;
	std::string value;
	
	while(getline(file,line))
	{
		/*
		Ignore empty lines
		*/
		if(!line.length())
			continue;		
		/*
		Comment character
		*/
		if(!line.at(0)=='#')
			continue;
		
		/*
		key contains everything before the '=', and value contains
		everything after it.
		*/
		key=line.substr(0,line.find('='));
		value=line.substr(line.find('=')+1);
		
		/*
		Trim whitespace.
		*/
		key=trim(key);
		value=trim(value);
		
		/*
		Check if the value is a string.
		*/
		if(value.at(0)=='"')
		{
			/*
			Trim the quotes.
			*/
			value=trim(value,"\"");
		}
		
		if(key!="")
		{		
			m_values[key]=value;
		}
	}
	
	file.close();
	
	return true;
}



bool IniFile::save(const std::string& filename)
{
	std::ofstream file(filename.c_str(),std::ios_base::trunc);
	
	if(!file.good())	
	{
		std::cerr<<"Cannot open file "<<filename<<" for writing"<<std::endl;
		return false;
	}
	
	std::map<std::string,std::string>::iterator i;
	
	for(i=m_values.begin();i!=m_values.end();i++)
	{		
		file<<i->first<<"="<<i->second<<std::endl;
	}
	
	file.close();
	
	return true;
}

IniFile::IniFile()
{

}

IniFile::IniFile(const std::string& filename)
{
	load(filename);
}



