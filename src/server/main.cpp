#include <iostream>
#include <string>

#include "shared/inifile.hpp"

int main(int argc,char** argv)
{
	std::cout<<"Kiihdytyspeli 2 server"<<std::endl;
	
	std::string config;
	int port;
	
	for(int i=0;i<argc;i++)
	{
		std::string arg=argv[i];

		if(arg==std::string("-config"))
		{
			if(i==argc-1)
			{
				std::cerr<<"expected parameter for \"-config\""<<std::endl;
				return 1;
			}
			
			config=argv[++i];		
		}
			
		if(arg==std::string("-port"))
		{
			if(i==argc-1)
			{
				std::cerr<<"expected parameter for \"-port\""<<std::endl;
				return 1;
			}
			
			int num;
			std::istringstream ss(argv[++i]);
			
			if(!(ss>>num))
			{
				std::cerr<<"expected number value for \"-port\""<<std::endl;
			}
			
			port=num;
		}			
	}
	
	std::cout<<"port="<<port<<std::endl;
	std::cout<<"config="<<config<<std::endl;
	
	
	IniFile inifile(config);
	
	//check for new connections to accept
	//process messages
}

