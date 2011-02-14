#include "connection.hpp"

#include "gamestate.hpp"

#include "net/clientsocket.hpp"

#include "protocol/protocol.hpp"
#include "protocol/setname.hpp"
#include "protocol/buypart.hpp"
#include "protocol/buyvehicle.hpp"
#include "protocol/setactivevehicle.hpp"
#include "protocol/playerinfo.hpp"
#include "protocol/shopvehicle.hpp"
#include "protocol/shoppart.hpp"
#include "protocol/collection.hpp"
#include "protocol/vehicle.hpp"
#include "protocol/part.hpp"

#include <sstream>
#include <algorithm>
#include <iostream>
#include <limits>

void Connection::processPackets(ClientSocket& socket)
{
	int bytesRead;

	while((bytesRead = socket.read(scrapBuffer, BUFFERSIZE)) > 0)
	{
		receiveBuffer.append(scrapBuffer, bytesRead);
	}
	
	if(bytesRead == -1)
	{
		return;
	}
	
	while(1)
	{
		Packet packet;
	
		try
		{
			packet.readFromBuffer(receiveBuffer);
		}
		catch(EndOfDataException)
		{
			break;		
		}
		
		try
		{			
			uint16_t type = packet.getType();
			
			if(type == Protocol::COMMAND_SET_NAME)
			{
				Protocol::SetName setName;

				packet >> setName;
				
				gameState.getPlayer(playerId).setName(setName.name);
								
				sendPlayerInfo();
			}
			else if(type == Protocol::COMMAND_SET_ACTIVE_VEHICLE_ID)
			{
				Protocol::SetActiveVehicle command;

				packet >> command;
				
				gameState.getPlayer(playerId).setActiveVehicleId(command.id);
								
				sendActiveVehicleId();				
			}
			else if(type == Protocol::COMMAND_BUY_VEHICLE)
			{
				Protocol::BuyVehicle buyVehicle;

				packet >> buyVehicle;
				
				gameState.getPlayer(playerId).buyVehicle(buyVehicle.id);
								
				sendPlayerInfo();
				sendPlayerVehicles();				
			}
			else if(type == Protocol::COMMAND_BUY_PART)
			{
				Protocol::BuyPart buyPart;

				packet >> buyPart;
				
				gameState.getPlayer(playerId).buyPart(buyPart.id);
								
				sendPlayerInfo();
				sendPlayerParts();				
			}
		}
		catch(EndOfDataException)
		{
			std::cerr << "Invalid packet!" << std::endl;
			std::cerr << packet << std::endl;
		}
		catch(InsufficientMoneyException)
		{
			std::cerr << "Out of money!" << std::endl;
		}
	}
	
	writePackets(socket);
}

void Connection::writePackets(ClientSocket& socket)
{
	while(sendQueue.size() > 0)
	{
		std::string packetString = sendQueue.front().getString();
		
		socket.write(packetString.c_str(), packetString.size());
		
		sendQueue.pop();
	}
}

void Connection::sendPlayerInfo()
{
	Packet packet;
	
	packet.setType(Protocol::DATA_PLAYER_INFO);
	
	Protocol::PlayerInfo playerInfo;
		
	Player& player = gameState.getPlayer(playerId);
	
	playerInfo.playerId = playerId;	
	playerInfo.name = player.getName();
	playerInfo.money = player.getMoney();

	packet << playerInfo;
	
	sendQueue.push(packet);	
}

void Connection::sendPlayers()
{
	Packet packet;
	
	packet.setType(Protocol::DATA_PLAYERS);
	
	Protocol::Collection<Protocol::PlayerInfo> playerCollection;
	
	std::vector<int> playerIds = gameState.getPlayerIds();
	std::vector<int>::iterator i;
	
	for(i = playerIds.begin(); i != playerIds.end(); ++i)
	{
		Protocol::PlayerInfo playerInfo;
			
		const Player& player = gameState.getPlayer((*i));
		
		playerInfo.playerId = (*i);	
		playerInfo.name = player.getName();
		
		/*
		The amount of money is secret to other players, but we still have to
		define it because of the reusing of the PlayerInfo class.
		*/
		playerInfo.money = 0;
		
		playerCollection.addItem(playerInfo);
	}
		
	packet << playerCollection;
	
	sendQueue.push(packet);	
}

void Connection::sendShopVehicles()
{
	Packet packet;
	
	packet.setType(Protocol::DATA_SHOP_VEHICLES);
	
	Protocol::Collection<Protocol::ShopVehicle> shopVehiclesCollection;
	
	std::vector<std::string> vehicleModelIds = gameState.getVehicleModelIds();
	std::vector<std::string>::iterator i;
	
	for(i = vehicleModelIds.begin(); i != vehicleModelIds.end(); ++i)
	{
		Protocol::ShopVehicle shopVehicle;
			
		const VehicleModel& vehicleModel = gameState.getVehicleModel((*i));
		
		shopVehicle.id = (*i);
		shopVehicle.name = vehicleModel.getName();
		shopVehicle.info = vehicleModel.getInfo();
		shopVehicle.imageName = vehicleModel.getImageName();
		shopVehicle.year = vehicleModel.getYear();
		shopVehicle.chassisWeight = vehicleModel.getChassisWeight();
		shopVehicle.price = vehicleModel.getPrice();
		
		shopVehiclesCollection.addItem(shopVehicle);
	}
		
	packet << shopVehiclesCollection;
	
	sendQueue.push(packet);	
}

void Connection::sendShopParts()
{
	Packet packet;
	
	packet.setType(Protocol::DATA_SHOP_PARTS);
	
	Protocol::Collection<Protocol::ShopPart> shopPartsCollection;
	
	std::vector<std::string> PartModelIds = gameState.getPartModelIds();
	std::vector<std::string>::iterator i;
	
	for(i = PartModelIds.begin(); i != PartModelIds.end(); ++i)
	{
		Protocol::ShopPart shopPart;
			
		const PartModel& PartModel = gameState.getPartModel((*i));
		
		shopPart.id = (*i);
		shopPart.name = PartModel.getName();
		shopPart.type = PartModel.getType();
		shopPart.price = PartModel.getPrice();
		shopPart.weight = PartModel.getWeight();
				
		shopPartsCollection.addItem(shopPart);
	}
		
	packet << shopPartsCollection;
	
	sendQueue.push(packet);	
}

void Connection::sendPlayerVehicles()
{
	Packet packet;
	
	packet.setType(Protocol::DATA_PLAYER_VEHICLES);
	
	Protocol::Collection<Protocol::Vehicle> playerVehicleCollection;
	
	Player& player = gameState.getPlayer(playerId);
	
	for(int i = 0; i < player.getVehicleCount(); ++i)
	{
		Protocol::Vehicle playerVehicle;
			
		const Vehicle& vehicle = player.getVehicle(i);
		
		playerVehicle.id = i;
		playerVehicle.name = vehicle.getModel().getName();
		playerVehicle.info = vehicle.getModel().getInfo();
		playerVehicle.imageName = vehicle.getModel().getImageName();
		playerVehicle.year = vehicle.getModel().getYear();
		playerVehicle.chassisWeight = vehicle.getModel().getChassisWeight();
		playerVehicle.price = vehicle.getModel().getPrice();
		
		playerVehicleCollection.addItem(playerVehicle);
	}
		
	packet << playerVehicleCollection;
	
	sendQueue.push(packet);	
}

void Connection::sendPlayerParts()
{
	Packet packet;
	
	packet.setType(Protocol::DATA_PLAYER_PARTS);
	
	Protocol::Collection<Protocol::Part> playerPartCollection;
	
	Player& player = gameState.getPlayer(playerId);
	
	for(int i = 0; i < player.getPartCount(); ++i)
	{
		Protocol::Part playerPart;
			
		const Part& Part = player.getPart(i);
		
		playerPart.id = i;
		
		playerPart.name = Part.getName();
		playerPart.type = Part.getType();
		playerPart.price = Part.getPrice();
		playerPart.weight = Part.getWeight();

		playerPartCollection.addItem(playerPart);
	}
		
	packet << playerPartCollection;
	
	sendQueue.push(packet);
}

void Connection::sendActiveVehicleId()
{
	Packet packet;
	
	packet.setType(Protocol::DATA_ACTIVE_VEHICLE_ID);
	
	Protocol::ActiveVehicleId activeVehicleId;
	
	activeVehicleId = gameState.getPlayer(playerId).getActiveVehicleId();
	
	packet << activeVehicleId;
	
	sendQueue.push(packet);
}

Connection::Connection(GameState& gameState,int playerId):
	gameState(gameState),
	playerId(playerId)	
{
	sendPlayerInfo();
	sendPlayers();
	sendShopParts();
	sendShopVehicles();
	sendPlayerVehicles();
}
