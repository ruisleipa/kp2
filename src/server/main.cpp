#include <iostream>
#include <string>
#include <map>

#include "shared/inifile.hpp"
#include "shared/serversocket.hpp"
#include "shared/socketset.hpp"
#include "shared/outputredirector.hpp"

#include "connection.hpp"

int main(int argc,char** argv)
{
	OutputRedirector redirec("server.log");

	std::cout<<"Kiihdytyspeli 2 server"<<std::endl;
	
	std::string config="cfg/server.cfg";
	int port=31000;
	
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
	
	std::cout<<"Listening on port: "<<port<<std::endl;
	
	ServerSocket socket;
	socket.open(port);
	
	SocketSet set;
	set.add(&socket);
	
	std::cout<<"Reading config file: "<<config<<std::endl;	
	
	IniFile inifile(config);
	
	std::map<ClientSocket*,Connection> connections;
	
	const int BUFFERSIZE=1024;
	
	char buf[BUFFERSIZE];
	
	while(1)
	{
		SocketActivity activity;
	
		activity=set.waitForActivity();
		
		if(activity.getSocket()==&socket)
		{
			/* Accept the new connection. */
			
			ClientSocket* newconnection=new ClientSocket;
			
			if(socket.accept(*newconnection)==0)
			{			
				set.add(newconnection);
				connections[newconnection];
			
				std::cout<<"New connection"<<std::endl;
			}
		}
		else
		{		
			ClientSocket* conn=(ClientSocket*)activity.getSocket();
			
			if(activity.canRead())
			{
				int read;
			
				/*
				Read as long as there is data to read (reads more than
				zero bytes).
				*/
				while((read=conn->read(buf,BUFFERSIZE))>0)
				{
					std::cout<<"Got "<<read<<" bytes."<<std::endl;

					connections[conn].readFromClient(buf,read);
				}
						
				/*
				ClientSocket::read returns -1 when the connection has
				been closed. We remove the connection from our tables.
				*/
				if(read==-1)
				{
					set.remove(conn);
					connections.erase(conn);
				
					delete conn;
			
					std::cout<<"Connection closed"<<std::endl;
					
					continue;
				}
			}
			
			if(activity.canWrite())
			{
				int written;
			
				/*
				Write as long as can be written.
				*/				
				connections[conn].writeToClient(conn);
			}
		}
	}
}

