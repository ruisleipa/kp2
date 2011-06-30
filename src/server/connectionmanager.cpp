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
				ClientSocket* socket = dynamic_cast<ClientSocket*>(activity.socket);
				
				try
				{
					if(activity.canRead)
						readFromSocket(socket);
					
					writeToSocket(socket);
				}
				catch(ConnectionClosedException& e)
				{
					std::cerr << "Connection closed: ";
					std::cerr << e.getMessage();
					std::cerr << std::endl;
				
					closeConnectionBySocket(socket);
				}
			}
		}
	}
}

int ConnectionManager::getConnectionCount()
{
	return connections.size();
}

Connection& ConnectionManager::getConnectionByIndex(int index)
{
	std::map<ClientSocket*, Connection>::iterator i;
	
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
	ClientSocket socket;

	serverSocket.accept(socket);

	Player player("pelaaja", 20000);
	int playerId = gameState.addPlayer(player);
	
	sockets.push_back(socket);
	
	Connection connection(gameState, playerId, sockets.back(), simulationState);
	connections.insert(std::make_pair(&sockets.back(), connection));
	socketSet.add(&sockets.back());
	
	std::cout << "New connection" << std::endl;
}

void ConnectionManager::readFromSocket(ClientSocket* socket)
{
	Connection& connection = connections.at(socket);
	
	connection.processPackets();
}

void ConnectionManager::writeToSocket(ClientSocket* socket)
{
	Connection& connection = connections.at(socket);
	
	connection.writePackets();
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

ConnectionManager::ConnectionManager(ServerSocket& serverSocket, GameState& gameState, SimulationState& simulationState):
	serverSocket(serverSocket),
	gameState(gameState),
	simulationState(simulationState)
{
	socketSet.add(&serverSocket);
}
