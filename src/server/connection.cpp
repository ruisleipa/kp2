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

				Game::Object* object = objectIdMapper.getObject(call["id"].asString());

				if(object)
				{
					if(Game::Player* player = dynamic_cast<Game::Player*>(object))
					{
						if(player != this->player)
						{
							std::cout << "Connection invoked method on non-owned player." << std::endl;
						}

						std::string method = call["method"].asString();
						Json::Value& arguments = call["arguments"];

						if(method == "setName")
						{
							std::string name = arguments["name"].asString();

							player->setName(name);
						}
						else if(method == "setActiveVehicle")
						{
							Game::Vehicle* vehicle = objectIdMapper.getTypedObject<Game::Vehicle*>(arguments["vehicle"].asString());

							player->setActiveVehicle(vehicle);
						}
						else if(method == "buyPart")
						{
							Game::Part* part = objectIdMapper.getTypedObject<Game::Part*>(arguments["part"].asString());

							player->buyPart(part);
						}
						else if(method == "buyVehicle")
						{
							Game::Vehicle* vehicle = objectIdMapper.getTypedObject<Game::Vehicle*>(arguments["vehicle"].asString());

							player->buyVehicle(vehicle);
						}
						else
						{
							std::cout << "Unimplemented method of class Player" << method << std::endl;
						}
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

void Connection::addIds(Json::Value& value)
{
	if(value.isObject() && value.isMember("__pointer"))
	{
		Game::Object* object = (Game::Object*)value["__pointer"].asUInt();

		value["__id"] = objectIdMapper.getId(object);
	}

	if(value.isObject() || value.isArray())
		for(auto& child : value)
			addIds(child);
}

Connection::Connection(Game::State& gameState, Game::Player* player, Net::ClientSocket& socket):
	gameState(gameState),
	player(player),
	socket(&socket)
{
	Json::Value state;
	gameState.save(state);

	addIds(state);

	std::cout << state << std::endl;

	state["client"]["playerId"] = gameState.getPlayers().getIndexOf(player);

	Json::FastWriter fw;

	Net::Packet packet;
	packet.setType(Protocol::GAME_STATE);

	packet << fw.write(state);

	writePacket(packet);
	writeBufferedData();
}

