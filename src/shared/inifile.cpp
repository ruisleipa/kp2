#include "inifile.hpp"

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


int IniFile::load(const std::string& filename)
{
	std::ifstream file(filename.c_str(),std::ios_base::in);
	
	if(!file.good())	
	{
		std::cerr<<"Cannot open file "<<filename<<" for reading"<<std::endl;
		return -1;
	}
	
	std::string line;
	std::string key;
	std::string value;
	
	while(getline(file,line))
	{
		if(!line.length())
			continue;		
		if(!line.at(0)=='#')
			continue;
		
		key=line.substr(0,line.find('='));
		value=line.substr(line.find('=')+1);
		
		if(key!="")
		{		
			m_values[key]=value;
		}
	}
	
	file.close();
	
	return 0;
}



int IniFile::save(const std::string& filename)
{
	std::ofstream file(filename.c_str(),std::ios_base::trunc);
	
	if(!file.good())	
	{
		std::cerr<<"Cannot open file "<<filename<<" for writing"<<std::endl;
		return -1;
	}
	
	std::map<std::string,std::string>::iterator i;
	
	for(i=m_values.begin();i!=m_values.end();i++)
	{		
		file<<i->first<<"="<<i->second<<std::endl;
	}
	
	file.close();
	
	return 0;
}

IniFile::IniFile()
{

}

IniFile::IniFile(const std::string& filename)
{
	load(filename);
}



