#include <iostream>
#include <string>
#include <map>

#include "shared/inifile.hpp"
#include "shared/serversocket.hpp"
#include "shared/socketset.hpp"
#include "shared/protocol.hpp"

#include "shared/outputredirector.hpp"
#include "shared/crashmessage.hpp"
#include "shared/crashcatcher.hpp"

#include "connection.hpp"

int main(int argc,char** argv)
{
	CrashMessage crash_message;

	CrashCatcher crash_handler(crash_message);

	OutputRedirector redirec("server.log");

	std::cout<<"Kiihdytyspeli 2 server"<<std::endl;
	
	std::string config="cfg/server.cfg";
	int port=31000;
	bool local=true;
	bool quit_when_empty=false;
	int connection_limit=8;
	
	for(int i=1;i<argc;i++)
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
		else if(arg==std::string("-port"))
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
		else
		{
			std::cerr<<"unknown parameter \""<<arg<<"\""<<std::endl;
		}
	}
	
	std::cout<<"Listening on port: "<<port<<std::endl;
	
	ServerSocket socket;
	
	if(local)
		socket.open("localhost",port);
	else
		socket.open("",port);
	
	SocketSet set;
	set.add(&socket);
	
	std::cout<<"Reading config file: "<<config<<std::endl;	
	
	IniFile inifile(config);
	
	inifile.getValue("Server.LocalServer",local);
	inifile.getValue("Server.QuitWhenEmpty",quit_when_empty);	
	inifile.getValue("Server.ConnectionLimit",connection_limit);
	
	if(local)
		std::cout<<"Starting local server."<<std::endl;
		
	if(quit_when_empty)
		std::cout<<"Quitting when empty."<<std::endl;
		
	std::cout<<"Connection limit: "<<connection_limit<<std::endl;
	
	std::map<ClientSocket*,Connection> connections;

	while(1)
	{
		SocketActivity activity;
	
		activity=set.waitForActivity();
		
		if(activity.getSocket()==&socket)
		{
			/* Accept the new connection. */
			
			ClientSocket* newconnection=new ClientSocket;
			
			if(socket.accept(*newconnection) == true)
			{	
				if(connections.size()==connection_limit)
				{
					delete newconnection;
				
					continue;
				}
			
				set.add(newconnection);
				connections[newconnection];
			
				std::cout<<"New connection"<<std::endl;
			}
		}
		else
		{			
			ClientSocket* conn=(ClientSocket*)activity.getSocket();			
			
			if(connections[conn].readFromClient((ClientSocket*)activity.getSocket()) == false)
			{
				set.remove(conn);
				connections.erase(conn);
			
				delete conn;
		
				std::cout<<"Connection closed"<<std::endl;
				
				if(connections.size()==0 && quit_when_empty)
				{
					break;
				}
				else
				{
					std::cout<<"continue"<<std::endl;
					continue;
				}
					
			}
			
			
		}
	}
	
	std::cout<<"Server shutting down..."<<std::endl;
	
	remove("serverport.tmp");
}

