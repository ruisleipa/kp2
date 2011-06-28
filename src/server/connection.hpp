#ifndef CONNECTION_HPP
#define CONNECTION_HPP

#include <string>
#include <queue>

#include "net/packet.hpp"

class Player;
class ClientSocket;
class GameState;
class SimulationState;

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
		
		void sendPacket(const Packet& packet);
		
		Player& getPlayer();
		
		ClientSocket* getSocket();
	
		Connection(GameState& gameState, int playerId, ClientSocket& socket, SimulationState& simulationState);
		
	private:
		std::string receiveBuffer;
		char scrapBuffer[BUFFERSIZE];
		
		std::queue<Packet> sendQueue;
		
		GameState& gameState;
		int playerId;
		ClientSocket* socket;
		
		SimulationState& simulationState;
};

#endif // CONNECTION_HPP

