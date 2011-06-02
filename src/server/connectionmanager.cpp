#include "connectionmanager.hpp"

#include "utils/timer.hpp"

void ConnectionManager::processConnections(float timeoutInSeconds)
{
	Timer timer;

	while(timer.getSeconds() <= timeoutInSeconds)
	{
		SocketActivity activity = socketSet.waitForActivity(timeoutInSeconds * 1000.0);

		if(activity.timeoutExpired == false && activity.socket != 0)
		{
			if(activity.socket == &serverSocket)
			{
				acceptConnection();
			}
			else
			{
				if(activity.canRead)
					readFromSocket(dynamic_cast<ClientSocket*>(activity.socket));
				if(activity.canWrite)
					writeToSocket(dynamic_cast<ClientSocket*>(activity.socket));
			}
		}
	}
}

int ConnectionManager::getConnectionCount()
{
	return connections.size();
}

void ConnectionManager::acceptConnection()
{
	ClientSocket socket;

	serverSocket.accept(socket);

	Player player("pelaaja", 20000);
	int playerId = gameState.addPlayer(player);
	
	Connection connection(gameState, playerId);
	
	sockets.push_back(socket);
	
	connections.insert(std::make_pair(&sockets.back(), connection));
	socketSet.add(&sockets.back());
}

void ConnectionManager::readFromSocket(ClientSocket* socket)
{
	Connection& connection = connections.at(socket);
	
	try
	{
		connection.processPackets(*socket);
	}
	catch(ConnectionClosedException)
	{
		closeConnectionBySocket(socket);
	}
}

void ConnectionManager::writeToSocket(ClientSocket* socket)
{
	Connection& connection = connections.at(socket);
	
	try
	{
		connection.writePackets(*socket);
	}
	catch(ConnectionClosedException)
	{
		closeConnectionBySocket(socket);
	}
}

void ConnectionManager::closeConnectionBySocket(ClientSocket* socket)
{
	socketSet.remove(socket);
	connections.erase(socket);
	
	std::list<ClientSocket>::iterator i;
	
	for(i = sockets.begin(); i != sockets.end(); ++i)
	{
		ClientSocket* s = &(*i);
	
		if(socket == s)
		{
			sockets.erase(i);
			break;
		}
	}
}

ConnectionManager::ConnectionManager(ServerSocket& serverSocket, GameState& gameState):
	serverSocket(serverSocket),
	gameState(gameState)
{
	socketSet.add(&serverSocket);
}
