#include <iostream>
#include <string>
#include <map>

#include "utils/inifile.hpp"
#include "utils/outputredirector.hpp"
#include "utils/commandlineparser.hpp"

#include "net/serversocket.hpp"
#include "net/socketset.hpp"

#include "debug/crashmessage.hpp"
#include "debug/crashcatcher.hpp"

#include "gamestate.hpp"
#include "part.hpp"
#include "vehicle.hpp"
#include "connection.hpp"

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
	serverSocket.open(hostName,port);
	
	SocketSet sockets;
	
	sockets.add(&serverSocket);

	bool running = true;
	
	std::map<std::tr1::shared_ptr<ClientSocket>, Connection> connections;
	
	while(running)
	{
		SocketActivity activity = sockets.waitForActivity();
		
		if(activity.getSocket() == &serverSocket)
		{
			std::tr1::shared_ptr<ClientSocket> socket(new ClientSocket);
			
			serverSocket.accept(*socket.get());
			
			Player player("pelaaja", 20000);
			
			int playerId = gameState.addPlayer(player);
		
			Connection connection(gameState, playerId);
			
			connections.insert(std::make_pair(socket, connection));
			
			sockets.add(socket.get());
			
			connection.writePackets(*socket.get());
		}
		else
		{
			std::map<std::tr1::shared_ptr<ClientSocket>, Connection>::iterator i;
			
			for(i = connections.begin(); i != connections.end(); ++i)
			{	
				if(i->first.get() == activity.getSocket())
				{
					try
					{
						i->second.processPackets(*((ClientSocket*)activity.getSocket()));
					}
					catch(ConnectionClosedException)
					{
						sockets.remove(activity.getSocket());
					
						connections.erase(i);
					}
					
					break;
				}
			}
		}
		
		if(quitWhenEmpty && connections.size() == 0)
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

