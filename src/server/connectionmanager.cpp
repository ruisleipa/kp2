#include "connectionmanager.hpp"

#include "game/player.hpp"

#include <stdexcept>
#include <iostream>

void ConnectionManager::processConnections()
{
	Net::SocketActivity activity = socketSet.waitForActivity();

	if(activity.socket == &serverSocket)
	{
		acceptConnection();
	}
	else
	{
		Net::ClientSocket* socket = dynamic_cast<Net::ClientSocket*>(activity.socket);
		
		try
		{
			if(activity.canRead)
				readFromSocket(socket);
			
			writeToSocket(socket);
		}
		catch(Net::ConnectionClosedException& e)
		{
			std::cerr << "Connection closed: ";
			std::cerr << e.getMessage();
			std::cerr << std::endl;
		
			closeConnectionBySocket(socket);
		}
	}
}

int ConnectionManager::getConnectionCount()
{
	return connections.size();
}

Connection& ConnectionManager::getConnectionByIndex(int index)
{
	std::map<Net::ClientSocket*, Connection>::iterator i;
	
	i = connections.begin();
	
	while(index > 0) 
	{
		if(i == connections.end())
			throw std::runtime_error("No connection for index");
		
		i++;
		
		index--;
	}
	
	return i->second;
}

void ConnectionManager::acceptConnection()
{
	Net::ClientSocket socket;

	serverSocket.accept(socket);

	Game::Player* player = gameState.createPlayer();

	player->setMoney(5000);
	
	sockets.push_back(socket);
	
	Connection connection(gameState, player, sockets.back());
	connections.insert(std::make_pair(&sockets.back(), connection));
	socketSet.add(&sockets.back());
	
	std::cout << "New connection" << std::endl;
}

void ConnectionManager::readFromSocket(Net::ClientSocket* socket)
{
	Connection& connection = connections.at(socket);
	
	connection.processReceivedData();
}

void ConnectionManager::writeToSocket(Net::ClientSocket* socket)
{
	Connection& connection = connections.at(socket);
	
	connection.writeBufferedData();
}

void ConnectionManager::closeConnectionBySocket(Net::ClientSocket* socket)
{
	socketSet.remove(socket);
	connections.erase(socket);
	
	std::list<Net::ClientSocket>::iterator i;
	
	for(i = sockets.begin(); i != sockets.end(); ++i)
	{
		Net::ClientSocket* s = &(*i);
	
		if(socket == s)
		{
			sockets.erase(i);
			break;
		}
	}
}

ConnectionManager::ConnectionManager(Net::ServerSocket& serverSocket, Game::State& gameState):
	serverSocket(serverSocket),
	gameState(gameState)
{
	socketSet.add(&serverSocket);
}

