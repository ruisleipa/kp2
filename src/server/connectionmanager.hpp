#ifndef SERVER_CONNECTIONMANAGER_HPP
#define SERVER_CONNECTIONMANAGER_HPP

#include <map>
#include <list>

#include "game/state.hpp"
#include "connection.hpp"

#include "net/socketset.hpp"
#include "net/clientsocket.hpp"
#include "net/serversocket.hpp"

// This class handles the mapping of sockets to connections
class ConnectionManager
{
	public:
		void processConnections();

		int getConnectionCount();
		Connection& getConnectionByIndex(int index);

		ConnectionManager(Net::ServerSocket&, Game::State&);

	private:
		void acceptConnection();
		void readFromSocket(Net::ClientSocket* socket);
		void writeToSocket(Net::ClientSocket* socket);
		void closeConnectionBySocket(Net::ClientSocket* socket);

		Net::ServerSocket& serverSocket;
		Game::State& gameState;

		std::map<Net::ClientSocket*, Connection> connections;
		std::list<Net::ClientSocket> sockets;

		Net::SocketSet socketSet;

};

#endif

