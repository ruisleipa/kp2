#include <iostream>
#include <string>

#include "utils/inifile.hpp"
#include "utils/outputredirector.hpp"
#include "utils/commandlineparser.hpp"
#include "utils/timer.hpp"

#include "net/serversocket.hpp"

#include "debug/crashmessage.hpp"
#include "debug/crashcatcher.hpp"

#include "connectionmanager.hpp"
#include "game/objectfactory.hpp"
#include "game/state.hpp"

void startServer(int argc,char** argv)
{
	std::cout<<"Kiihdytyspeli 2 Server"<<std::endl;
	
	CommandLineParser commandLineParser(argc,argv);
	
	std::string configPath="cfg/server.cfg";
	
	commandLineParser.getValue("config",configPath);
	
	std::cout<<"Reading config from \""<<configPath<<"\"."<<std::endl;
	
	Json::Value config;
	
	std::ifstream configStream(configPath);
	
	configStream >> config;	
	
	unsigned int port = config["port"].asUInt();
	unsigned int connectionLimit = config["connectionLimit"].asUInt();
	bool quitWhenEmpty = config["quitWhenEmpty"].asBool();
	bool isLocal = config["isLocal"].asBool();
		
	std::cout<<"Reading game state from \"gamedata/beginstate.cfg\"."<<std::endl;
	
	Json::Value state;	
	std::ifstream stateStream("gamedata/beginstate.cfg");
	stateStream >> state;	
	
	Game::ObjectFactory objectFactory;
	Game::State gameState(state, objectFactory);
		
	std::string hostName;
	
	if(isLocal)
		hostName = "127.0.0.1";
	else
		hostName = "0.0.0.0";
	
	Net::ServerSocket serverSocket;
	
	serverSocket.open(hostName, port);
	
	ConnectionManager connectionManager(serverSocket, gameState);
	
	bool playersHaveJoined = false;
	bool running = true;

	while(running)
	{
		connectionManager.processConnections();
					
		if(connectionManager.getConnectionCount() > 0)
			playersHaveJoined = true;
		
		if(quitWhenEmpty && connectionManager.getConnectionCount() == 0 && playersHaveJoined)
			running = false;
	}
	
	Json::Value savedState;
	gameState.save(savedState);
	std::ofstream("autosave.txt") << savedState;
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

