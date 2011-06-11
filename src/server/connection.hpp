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
		void processPackets();
		void writePackets();
		
		void sendPlayerInfo();
		void sendPlayers();
		void sendShopVehicles();
		void sendShopParts();
		void sendPlayerVehicles();
		void sendPlayerParts();
		void sendActiveVehicleId();
		void sendInstallError(const std::string& error);
		void sendPerformanceData();
		
		void sendRaceState();
		void sendRaceStart();
		
		ClientSocket* getSocket();
	
		Connection(GameState& gameState, int playerId, ClientSocket& socket);
		
	private:
		std::string receiveBuffer;
		char scrapBuffer[BUFFERSIZE];
		
		std::queue<Packet> sendQueue;
		
		GameState& gameState;
		int playerId;
		ClientSocket* socket;
};

#endif // CONNECTION_HPP

