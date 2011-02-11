#include "connection.hpp"

#include "gamestate.hpp"

#include "net/clientsocket.hpp"

#include "protocol/protocol.hpp"
#include "protocol/setname.hpp"
#include "protocol/buypart.hpp"
#include "protocol/buyvehicle.hpp"
#include "protocol/playerinfo.hpp"
#include "protocol/players.hpp"
#include "protocol/playervehicles.hpp"
#include "protocol/playerparts.hpp"
#include "protocol/shopvehicles.hpp"
#include "protocol/shopparts.hpp"

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
			
			if(type == COMMAND_SET_NAME)
			{
				SetName setName;

				packet >> setName;
				
				gameState.getPlayer(playerId).setName(setName.name);
								
				sendPlayerInfo();
			}
			else if(type == COMMAND_BUY_VEHICLE)
			{
				BuyVehicle buyVehicle;

				packet >> buyVehicle;
				
				gameState.getPlayer(playerId).buyVehicle(buyVehicle.id);
								
				sendPlayerInfo();
				sendPlayerVehicles();				
			}
			else if(type == COMMAND_BUY_PART)
			{
				BuyPart buyPart;

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
	
	packet.setType(DATA_PLAYER_INFO);
	
	PlayerInfo playerInfo;
		
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
	
	packet.setType(DATA_PLAYERS);
	
	Players players;
	
	std::vector<int> playerIds = gameState.getPlayerIds();
	std::vector<int>::iterator i;
	
	for(i = playerIds.begin(); i != playerIds.end(); ++i)
	{
		PlayerInfo playerInfo;
			
		const Player& player = gameState.getPlayer((*i));
		
		playerInfo.playerId = (*i);	
		playerInfo.name = player.getName();
		
		/*
		The amount of money is secret to other players, but we still have to
		define it because of the reusing of the PlayerInfo class.
		*/
		playerInfo.money = 0;
		
		players.addPlayer(playerInfo);
	}
		
	packet << players;
	
	sendQueue.push(packet);	
}

void Connection::sendShopVehicles()
{
	Packet packet;
	
	packet.setType(DATA_SHOP_VEHICLES);
	
	ShopVehicles shopVehicles;
	
	std::vector<std::string> vehicleModelIds = gameState.getVehicleModelIds();
	std::vector<std::string>::iterator i;
	
	for(i = vehicleModelIds.begin(); i != vehicleModelIds.end(); ++i)
	{
		ShopVehicle shopVehicle;
			
		const VehicleModel& vehicleModel = gameState.getVehicleModel((*i));
		
		shopVehicle.id = (*i);
		shopVehicle.name = vehicleModel.getName();
		shopVehicle.info = vehicleModel.getInfo();
		shopVehicle.imageName = vehicleModel.getImageName();
		shopVehicle.year = vehicleModel.getYear();
		shopVehicle.chassisWeight = vehicleModel.getChassisWeight();
		shopVehicle.price = vehicleModel.getPrice();
		
		shopVehicles.addVehicle(shopVehicle);
	}
		
	packet << shopVehicles;
	
	sendQueue.push(packet);	
}

void Connection::sendShopParts()
{
	Packet packet;
	
	packet.setType(DATA_SHOP_PARTS);
	
	ShopParts shopParts;
	
	std::vector<std::string> PartModelIds = gameState.getPartModelIds();
	std::vector<std::string>::iterator i;
	
	for(i = PartModelIds.begin(); i != PartModelIds.end(); ++i)
	{
		ShopPart shopPart;
			
		const PartModel& PartModel = gameState.getPartModel((*i));
		
		shopPart.id = (*i);
		shopPart.name = PartModel.getName();
		shopPart.type = PartModel.getType();
		shopPart.price = PartModel.getPrice();
		shopPart.weight = PartModel.getWeight();
				
		shopParts.addPart(shopPart);
	}
		
	packet << shopParts;
	
	sendQueue.push(packet);	
}

void Connection::sendPlayerVehicles()
{
	Packet packet;
	
	packet.setType(DATA_PLAYER_VEHICLES);
	
	PlayerVehicles playerVehicles;
	
	Player& player = gameState.getPlayer(playerId);
	
	for(int i = 0; i < player.getVehicleCount(); ++i)
	{
		PlayerVehicle playerVehicle;
			
		const Vehicle& vehicle = player.getVehicle(i);
		
		playerVehicle.id = i;
		playerVehicle.name = vehicle.getModel().getName();
		playerVehicle.info = vehicle.getModel().getInfo();
		playerVehicle.imageName = vehicle.getModel().getImageName();
		playerVehicle.year = vehicle.getModel().getYear();
		playerVehicle.chassisWeight = vehicle.getModel().getChassisWeight();
		playerVehicle.price = vehicle.getModel().getPrice();
		
		playerVehicles.addVehicle(playerVehicle);
	}
		
	packet << playerVehicles;
	
	sendQueue.push(packet);	
}

void Connection::sendPlayerParts()
{
	Packet packet;
	
	packet.setType(DATA_PLAYER_PARTS);
	
	PlayerParts playerParts;
	
	Player& player = gameState.getPlayer(playerId);
	
	for(int i = 0; i < player.getPartCount(); ++i)
	{
		PlayerPart playerPart;
			
		const Part& Part = player.getPart(i);
		
		playerPart.id = i;
		
		playerPart.name = Part.getName();
		playerPart.type = Part.getType();
		playerPart.price = Part.getPrice();
		playerPart.weight = Part.getWeight();

		playerParts.addPart(playerPart);
	}
		
	packet << playerParts;
	
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
