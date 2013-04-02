#ifndef CONNECTION_HPP
#define CONNECTION_HPP

#include "net/packet.hpp"
#include "net/clientsocket.hpp"
#include "game/state.hpp"
#include <string>
#include "objectfactory.hpp"
#include "objectidmapper.hpp"

const int BUFFERSIZE=512;

class Connection
{
	public:
		void processReceivedData();
		void writeBufferedData();

		void writePacket(const Net::Packet& packet);

		Connection(Game::State& gameState, Game::Player* player, Net::ClientSocket& socket);

	private:
		void addIds(Json::Value &value);

		std::string receiveBuffer;
		std::string sendBuffer;
		char scrapBuffer[BUFFERSIZE];

		Game::State& gameState;
		Game::Player* player;
		Net::ClientSocket* socket;

		Server::ObjectIdMapper objectIdMapper;
};

#endif // CONNECTION_HPP

