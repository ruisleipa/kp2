#include <iostream>
#include <string>

#include "utils/inifile.hpp"
#include "utils/outputredirector.hpp"
#include "utils/commandlineparser.hpp"

#include "net/serversocket.hpp"

#include "debug/crashmessage.hpp"
#include "debug/crashcatcher.hpp"

#include "connectionmanager.hpp"
#include "gamestate.hpp"

void startServer(int argc,char** argv)
{
	std::cout<<"Kiihdytyspeli 2 Server"<<std::endl;
	
	CommandLineParser commandLineParser(argc,argv);
	
	std::string configPath="cfg/server.cfg";
	
	commandLineParser.getValue("config",configPath);
	
	std::cout<<"Reading config from \""<<configPath<<"\"."<<std::endl;
	
	IniFile config(configPath);
	
	int port;
	int connectionLimit;
	int quitWhenEmpty;
	int isLocal;
	
	config.getValue("port",port);
	config.getValue("isLocal",isLocal);
	config.getValue("quitWhenEmpty",quitWhenEmpty);
	config.getValue("connectionLimit",connectionLimit);
	
	GameState gameState;
	
	std::string hostName;
	
	if(isLocal)
		hostName = "127.0.0.1";
	else
		hostName = "0.0.0.0";
	
	ServerSocket serverSocket;
	
	serverSocket.open(hostName, port);
	
	ConnectionManager connectionManager(serverSocket, gameState);
	
	bool playersHaveJoined = false;
	bool running = true;
	
	while(running)
	{
		connectionManager.processConnections(0.001);
		
		if(connectionManager.getConnectionCount() > 0)
			playersHaveJoined = true;
		
		if(quitWhenEmpty && connectionManager.getConnectionCount() == 0 && playersHaveJoined)
			running = false;
	}	
}

int main(int argc,char** argv)
{
	CrashMessage crashMessage;
	CrashCatcher crashHandler(crashMessage);

	OutputRedirector redirect("server.log");

	try
	{
		startServer(argc,argv);
	}
	catch(std::exception& e)
	{
		std::cerr << e.what() << std::endl;
	}
	
	std::cout << "Server shutting down." <<std::endl;	
}

