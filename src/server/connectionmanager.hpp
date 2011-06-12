#ifndef SERVER_CONNECTIONMANAGER_HPP
#define SERVER_CONNECTIONMANAGER_HPP

#include <map>
#include <list>

#include "gamestate.hpp"
#include "connection.hpp"

#include "net/socketset.hpp"
#include "net/clientsocket.hpp"
#include "net/serversocket.hpp"

// This class handles the mapping of sockets to connections
class ConnectionManager
{
	public:
		void processConnections(float timeoutInSeconds);
		
		int getConnectionCount();
		Connection& getConnectionByIndex(int index);
		
		ConnectionManager(ServerSocket& serverSocket, GameState& gameState);
		
	private:
		void acceptConnection();
		void readFromSocket(ClientSocket* socket);
		void writeToSocket(ClientSocket* socket);
		void closeConnectionBySocket(ClientSocket* socket);
	
		ServerSocket& serverSocket;
		GameState& gameState;
		
		std::map<ClientSocket*, Connection> connections;
		std::list<ClientSocket> sockets;
		
		SocketSet socketSet;
		
};

#endif

