#include "connection.hpp"

#include <sstream>

#include "net/clientsocket.hpp"

#include "protocol/protocol.hpp"

#include "exceptions.hpp"

void Connection::processReceivedData()
{
	int bytesRead;

	while((bytesRead = socket->read(scrapBuffer, BUFFERSIZE)) > 0)
		receiveBuffer.append(scrapBuffer, bytesRead);
	
	if(bytesRead == -1)
		return;
	
	while(1)
	{
		Net::Packet packet;
	
		try
		{
			packet.readFromBuffer(receiveBuffer);
		}
		catch(Net::EndOfDataException)
		{
			break;		
		}
	}
	
	writeBufferedData();
}

void Connection::writeBufferedData()
{
	int written;

	while((written = socket->write(sendBuffer.c_str(), sendBuffer.size())) > 0)
			sendBuffer.erase(0, written);
}

void Connection::writePacket(const Net::Packet& packet)
{
	std::string str = packet.getString();

	sendBuffer.append(str.c_str(), str.size());
}

Connection::Connection(Game::State& gameState, Game::Player* player, Net::ClientSocket& socket):
	gameState(gameState),
	player(player),
	socket(&socket)
{
	Json::Value state;
	gameState.save(state);
	
	state["client"]["playerId"] = gameState.getId(player);
	
	Json::FastWriter fw;
	
	Net::Packet packet;
	
	packet << fw.write(state);
	
	writePacket(packet);
	writeBufferedData();
}

