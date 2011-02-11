#include "connection.hpp"

#include <iostream>
#include <stdint.h>

#include "utils/inifile.hpp"
#include "net/packet.hpp"
#include "net/clientsocket.hpp"
#include "protocol/protocol.hpp"

#include "protocol/setname.hpp"
#include "protocol/buyvehicle.hpp"
#include "protocol/buypart.hpp"

#include "utils/sdl.hpp"

bool Connection::connect(std::string hostname,int port)
{
	if(!socket.connect(hostname,port))
		return false;

	return true;
}

void Connection::processMessages()
{	
	int read,written;
	
	/*
	Read as long as there is data to read (reads more than
	zero bytes).
	*/
	while((read=socket.read(scrapBuffer,BUFFERSIZE))>0)
	{
		receiveBuffer.append(scrapBuffer,read);
	}
			
	/*
	Write as much as we can (writes more than
	zero bytes).
	*/
	while((written=socket.write(sendBuffer.c_str(),sendBuffer.size()))>0)
	{
		sendBuffer.erase(0,written);
	}
	
	while(1)
	{
		Packet message;
	
		try
		{
			message.readFromBuffer(receiveBuffer);
		}
		catch(EndOfDataException)
		{
			/*
			We don't have enough data for a packet, so we return.
			*/
			return;
		}
		
		try
		{
			std::cout << "RECEIVING" << std::endl << message << std::endl;
		
			switch(message.getType())
			{
				case DATA_PLAYER_INFO:
					message >> playerInfo;
					break;
				
				case DATA_PLAYERS:
					message >> players;
					break;
					
				case DATA_SHOP_VEHICLES:
					message >> shopVehicles;
					break;
					
				case DATA_SHOP_PARTS:
					message >> shopParts;
					break;
					
				case DATA_PLAYER_VEHICLES:
					message >> playerVehicles;
					break;
					
				case DATA_PLAYER_PARTS:
					message >> playerParts;
					break;
			}
		
			std::vector<std::tr1::function<void(Connection&)> >::iterator i;
			
			for(i=eventHandlers.begin();i!=eventHandlers.end();++i)
			{
				(*i)(*this);
			}	
		}
		catch(EndOfDataException)
		{
			std::cerr<<"Invalid packet!"<<std::endl;
			std::cerr<<message<<std::endl;
	
			return;
		}
	}
}

const PlayerInfo& Connection::getPlayerInfo()
{
	return playerInfo;
}

const Players& Connection::getPlayers()
{
	return players;
}

const ShopVehicles& Connection::getShopVehicles()
{
	return shopVehicles;
}

const ShopParts& Connection::getShopParts()
{
	return shopParts;
}

const PlayerVehicles& Connection::getPlayerVehicles()
{
	return playerVehicles;
}

const PlayerParts& Connection::getPlayerParts()
{
	return playerParts;
}

void Connection::setName(const std::string& name)
{
	Packet packet;
	
	packet.setType(COMMAND_SET_NAME);
	
	SetName setName;
	setName.name = name;
	
	packet << setName;
	
	writeToServer(packet);
}

void Connection::buyVehicle(const std::string& id)
{
	Packet packet;
	
	packet.setType(COMMAND_BUY_VEHICLE);
	
	BuyVehicle buyVehicle;
	buyVehicle.id = id;
	
	packet << buyVehicle;
	
	writeToServer(packet);
}

void Connection::buyPart(const std::string& id)
{
	Packet packet;
	
	packet.setType(COMMAND_BUY_PART);
	
	BuyPart buyPart;
	buyPart.id = id;
	
	packet << buyPart;
	
	writeToServer(packet);
}		

void Connection::setActiveVehicle(int vehiceId)
{

}

void Connection::addMachining(int vehiclePartId,const std::string& machiningId)
{

}

void Connection::installPart(int partId)
{

}

void Connection::uninstallPart(int vehiclePartId)
{

}

void Connection::writeToServer(const Packet& packet)
{
	std::cout << "SENDING" << std::endl << packet << std::endl;

	std::string str=packet.getString();

	sendBuffer.append(str.c_str(),str.size());
}

void Connection::addEventHandler(std::tr1::function<void(Connection&)> handler)
{
	eventHandlers.push_back(handler);
}

bool Connection::startLocalServer()
{
	IniFile settings;
	
	settings.setValue("port",31000);
	settings.setValue("isLocal",1);	
	settings.setValue("quitWhenEmpty",1);
	settings.setValue("connectionLimit",1);

	settings.save("cfg/singleplayer.cfg");

	std::string cmd;
	std::string args="-config cfg/singleplayer.cfg";

#ifdef WIN32
	cmd+="start kp2_server.exe ";
	cmd+=args;
#else
	cmd+="./kp2_server ";
	cmd+=args;
	cmd+=" &";
#endif		

	system(cmd.c_str());
	
	SDL_Delay(500);
	
	for(int i=0;i<10;i++)
	{	
		if(connect("localhost",31000))
			return true;
			
		SDL_Delay(50);
	}
	
	return false;
}

Connection::Connection()
{
	
}		
