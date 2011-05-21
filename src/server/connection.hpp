#ifndef CONNECTION_HPP
#define CONNECTION_HPP

#include <string>
#include <queue>

#include "net/packet.hpp"

class ClientSocket;
class GameState;

const int BUFFERSIZE=512;

class Connection
{
	public:
		void processPackets(ClientSocket& socket);
		void writePackets(ClientSocket& socket);
		
		void sendPlayerInfo();
		void sendPlayers();
		void sendShopVehicles();
		void sendShopParts();
		void sendPlayerVehicles();
		void sendPlayerParts();
		void sendActiveVehicleId();
		void sendInstallError(const std::string& error);
		void sendPerformanceData();
	
		Connection(GameState& gameState,int playerId);
		
	private:	
		std::string receiveBuffer;
		char scrapBuffer[BUFFERSIZE];
		
		std::queue<Packet> sendQueue;
		
		GameState& gameState;
		int playerId;
};

#endif // CONNECTION_HPP

