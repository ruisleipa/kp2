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

			if(packet.getType() == Protocol::REMOTE_INVOCATION)
			{
				std::string s;
				packet >> s;
				std::stringstream ss(s);
				Json::Value call;
				ss >> call;
				std::cout << "Remote invocation:" << call << std::endl;

				std::string type = call["objectType"].asString();
				int objectIndex = call["objectIndex"].asInt();

				if(type == "player")
				{
					Game::Player* player = gameState.getPlayers().getByIndex(objectIndex);

					if(player != this->player)
					{
						std::cout << "Connection invoked method on non-owned player." << std::endl;
					}

					std::string method = call["method"].asString();

					if(method == "setName")
					{
						std::string name = call["arguments"]["name"].asString();

						player->setName(name);
					}
					else if(method == "setActiveVehicle")
					{
						int vehicleIndex = call["arguments"]["vehicle"].asInt();

						Game::Vehicle* vehicle = player->getVehicles().getByIndex(vehicleIndex);

						player->setActiveVehicle(vehicle);
					}
					else if(method == "buyPart")
					{
						int partIndex = call["arguments"]["part"].asInt();

						Game::Part* part = gameState.getShopParts().getByIndex(partIndex);

						player->buyPart(part);
					}
					else if(method == "buyVehicle")
					{
						int vehicleIndex = call["arguments"]["vehicle"].asInt();

						Game::Vehicle* vehicle = gameState.getShopVehicles().getByIndex(vehicleIndex);

						player->buyVehicle(vehicle);
					}
					else
					{
						std::cout << "Unimplemented method of class " << type << ": " << method << std::endl;
					}
				}
			}
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

	state["client"]["playerId"] = gameState.getPlayers().getIndexOf(player);

	Json::FastWriter fw;

	Net::Packet packet;
	packet.setType(Protocol::GAME_STATE);

	packet << fw.write(state);

	writePacket(packet);
	writeBufferedData();
}

