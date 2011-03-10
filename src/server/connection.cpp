#include "connection.hpp"

#include "gamestate.hpp"

#include "net/clientsocket.hpp"

#include "protocol/protocol.hpp"
#include "protocol/setname.hpp"
#include "protocol/buypart.hpp"
#include "protocol/buyvehicle.hpp"
#include "protocol/setactivevehicle.hpp"
#include "protocol/installpart.hpp"
#include "protocol/uninstallpart.hpp"
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
				
				const VehicleModel& model = gameState.getVehicleModel(buyVehicle.id);
				
				gameState.getPlayer(playerId).buyVehicle(model);
				
				sendPlayerInfo();
				sendPlayerVehicles();				
			}
			else if(type == Protocol::COMMAND_BUY_PART)
			{
				Protocol::BuyPart buyPart;

				packet >> buyPart;
				
				const PartModel& model = gameState.getPartModel(buyPart.id);
				
				gameState.getPlayer(playerId).buyPart(model);
								
				sendPlayerInfo();
				sendPlayerParts();				
			}
			else if(type == Protocol::COMMAND_INSTALL_PART)
			{
				Protocol::InstallPart command;

				packet >> command;
				
				Player& player = gameState.getPlayer(playerId);
				Vehicle& vehicle = player.getVehicle(player.getActiveVehicleId());
					
				vehicle.installPart(command.id);
				
				sendPlayerParts();			
				sendPlayerVehicles();			
			}
			else if(type == Protocol::COMMAND_UNINSTALL_PART)
			{
				Protocol::UninstallPart command;

				packet >> command;
				
				Player& player = gameState.getPlayer(playerId);
				Vehicle& vehicle = player.getVehicle(player.getActiveVehicleId());
					
				vehicle.uninstallPart(command.id);
				
				sendPlayerParts();			
				sendPlayerVehicles();			
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
		catch(NoSuchPartException)
		{
			std::cerr << "No such part!" << std::endl;
		}
		catch(NoSuchVehicleException)
		{
			std::cerr << "No such vehicle!" << std::endl;
		}
		catch(PartDoesNotFitException e)
		{
			std::cerr << "Part does not fit: " << e.reason << std::endl;
			
			sendInstallError(e.reason);
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
	
	playerInfo.name = player.getName();
	playerInfo.money = player.getMoney();

	packet << playerInfo;
	
	sendQueue.push(packet);	
}

void Connection::sendPlayers()
{
	Packet packet;
	
	packet.setType(Protocol::DATA_PLAYERS);
	
	Protocol::Players players;
	
	std::vector<int> playerIds = gameState.getPlayerIds();
	std::vector<int>::iterator i;
	
	for(i = playerIds.begin(); i != playerIds.end(); ++i)
	{
		Protocol::PlayerInfo playerInfo;
			
		const Player& player = gameState.getPlayer((*i));
		
		playerInfo.name = player.getName();
		
		/*
		The amount of money is secret to other players, but we still have to
		define it because of the reusing of the PlayerInfo class.
		*/
		playerInfo.money = 0;
		
		players.addItem(*i, playerInfo);
	}
		
	packet << players;
	
	sendQueue.push(packet);	
}

void Connection::sendShopVehicles()
{
	Packet packet;
	
	packet.setType(Protocol::DATA_SHOP_VEHICLES);
	
	Protocol::ShopVehicles shopVehicles;
	
	std::vector<std::string> vehicleModelIds = gameState.getVehicleModelIds();
	std::vector<std::string>::iterator i;
	
	for(i = vehicleModelIds.begin(); i != vehicleModelIds.end(); ++i)
	{
		Protocol::ShopVehicle shopVehicle;
			
		const VehicleModel& vehicleModel = gameState.getVehicleModel((*i));
		
		shopVehicle.name = vehicleModel.getName();
		shopVehicle.info = vehicleModel.getInfo();
		shopVehicle.imageName = vehicleModel.getImageName();
		shopVehicle.year = vehicleModel.getYear();
		shopVehicle.chassisWeight = vehicleModel.getChassisWeight();
		shopVehicle.price = vehicleModel.getPrice();
		
		shopVehicles.addItem(*i, shopVehicle);
	}
		
	packet << shopVehicles;
	
	sendQueue.push(packet);	
}

void Connection::sendShopParts()
{
	Packet packet;
	
	packet.setType(Protocol::DATA_SHOP_PARTS);
	
	Protocol::ShopParts shopParts;
	
	std::vector<std::string> PartModelIds = gameState.getPartModelIds();
	std::vector<std::string>::iterator i;
	
	for(i = PartModelIds.begin(); i != PartModelIds.end(); ++i)
	{
		Protocol::ShopPart shopPart;
			
		const PartModel& PartModel = gameState.getPartModel((*i));
		
		shopPart.name = PartModel.getName();
		shopPart.type = PartModel.getType();
		shopPart.price = PartModel.getPrice();
		shopPart.weight = PartModel.getWeight();
				
		shopParts.addItem(*i, shopPart);
	}
		
	packet << shopParts;
	
	sendQueue.push(packet);	
}

void Connection::sendPlayerVehicles()
{
	Packet packet;
	
	packet.setType(Protocol::DATA_PLAYER_VEHICLES);
	
	Protocol::PlayerVehicles playerVehicles;
	
	Player& player = gameState.getPlayer(playerId);
	
	std::vector<int> ids = player.getVehicleIds();
	
	for(size_t i = 0; i < ids.size(); ++i)
	{
		Protocol::Vehicle playerVehicle;
			
		const Vehicle& vehicle = player.getVehicle(ids[i]);
		
		playerVehicle.name = vehicle.getModel().getName();
		playerVehicle.info = vehicle.getModel().getInfo();
		playerVehicle.imageName = vehicle.getModel().getImageName();
		playerVehicle.year = vehicle.getModel().getYear();
		playerVehicle.chassisWeight = vehicle.getModel().getChassisWeight();
		playerVehicle.totalWeight = vehicle.getWeight();
		playerVehicle.price = vehicle.getModel().getPrice();
		
		for(size_t j = 0; j < vehicle.getPartCount(); ++j)
		{
			Protocol::Part p;
			
			const Part& part = vehicle.getPart(j);
		
			p.name = part.getName();
			p.type = part.getType();
			p.price = part.getPrice();
			p.weight = part.getWeight();

			playerVehicle.parts.addItem(j, p);
		}
		
		playerVehicles.addItem(ids[i], playerVehicle);
	}
		
	packet << playerVehicles;
	
	sendQueue.push(packet);	
}

void Connection::sendPlayerParts()
{
	Packet packet;
	
	packet.setType(Protocol::DATA_PLAYER_PARTS);
	
	Protocol::PlayerParts playerParts;
	
	Player& player = gameState.getPlayer(playerId);
	
	std::vector<int> ids = player.getPartIds();
	
	for(size_t i = 0; i < ids.size(); ++i)
	{
		Protocol::Part playerPart;
			
		const Part& part = player.getPart(ids[i]);
		
		playerPart.name = part.getName();
		playerPart.type = part.getType();
		playerPart.price = part.getPrice();
		playerPart.weight = part.getWeight();

		playerParts.addItem(ids[i], playerPart);
	}
		
	packet << playerParts;
	
	sendQueue.push(packet);
}

void Connection::sendActiveVehicleId()
{
	Packet packet;
	
	packet.setType(Protocol::DATA_ACTIVE_VEHICLE_ID);
	
	Protocol::VehicleId activeVehicleId;
	
	activeVehicleId = gameState.getPlayer(playerId).getActiveVehicleId();
	
	packet << activeVehicleId;
	
	sendQueue.push(packet);
}

void Connection::sendInstallError(const std::string& error)
{
	Packet packet;
	
	packet.setType(Protocol::DATA_INSTALL_ERROR);
	
	Protocol::InstallError installError;
	
	installError = error;
	
	packet << installError;
	
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
