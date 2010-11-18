#include "commandlineparser.hpp"

bool CommandLineParser::getValue(const std::string& key,std::string& value)
{
	if(values.find(key) != values.end())
	{
		value=values[key];
		return true;
	}
	
	return false;	
}

CommandLineParser::CommandLineParser(int argc,char** argv)
{
	parse(argc,argv);
}

void CommandLineParser::parse(int argc,char** argv)
{
	for(int i = 1; i < argc; i++)
	{
		std::string arg = argv[i];
		
		if(arg.size() && arg.at(0) == '-')
		{
			if(i == argc - 1)
			{
				std::stringstream ss;
				
				ss << "Expected an value after '";
				ss << arg;
				ss << "'";
			
				throw CommandLineParseError(ss.str());
			}
			
			arg.erase(0,1);
			
			i++;
			
			values[arg]=argv[i];
			
			std::cout<<arg<<"='"<<values[arg]<<"'"<<std::endl;
		}
		else
		{
			std::stringstream ss;
		
			ss << "Expected a option instead of value '";
			ss << arg;
			ss << "'";
			
			throw CommandLineParseError(ss.str());
		}
	}
}



