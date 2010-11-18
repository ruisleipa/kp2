#include <iostream>
#include <string>
#include <map>

#include "utils/inifile.hpp"
#include "utils/outputredirector.hpp"
#include "utils/commandlineparser.hpp"

#include "net/serversocket.hpp"
#include "net/socketset.hpp"
#include "net/protocol.hpp"

#include "debug/crashmessage.hpp"
#include "debug/crashcatcher.hpp"

//#include "connection.hpp"

int main(int argc,char** argv)
{
	CrashMessage crashMessage;
	CrashCatcher crashHandler(crashMessage);

	OutputRedirector redirect("server.log");

	std::cout<<"Kiihdytyspeli 2 Server"<<std::endl;
	
	//int port=31000;
	//bool local=true;
	//bool quit_when_empty=false;
	//int connection_limit=8;
	
	CommandLineParser commandLineParser(argc,argv);
	
	std::string configPath="cfg/server.cfg";
	
	commandLineParser.getValue("config",configPath);
	
	IniFile config(configPath);
		
	//ConnectionListener newConnectionListener();

	std::cout<<configPath<<std::endl;
	
	while(1)
	{
		
	}

}

