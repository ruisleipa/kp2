#ifndef CONNECTION_HPP
#define CONNECTION_HPP

#include "net/packet.hpp"
#include "net/clientsocket.hpp"
#include "game/state.hpp"
#include <string>

const int BUFFERSIZE=512;

class Connection
{
	public:
		void processReceivedData();
		void writeBufferedData();

		void writePacket(const Net::Packet& packet);

		Connection(Game::State& gameState, Game::Player* player, Net::ClientSocket& socket);

	private:
		std::string receiveBuffer;
		std::string sendBuffer;
		char scrapBuffer[BUFFERSIZE];

		Game::State& gameState;
		Game::Player* player;
		Net::ClientSocket* socket;
};

#endif // CONNECTION_HPP

