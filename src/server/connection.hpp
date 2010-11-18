#ifndef CONNECTION_HPP
#define CONNECTION_HPP

#include <stdint.h>
#include <map>
#include <string>
#include <vector>

#include <tr1/memory>

#include "net/clientsocket.hpp"
#include "game/player.hpp"
#include "game/vehicle.hpp"

#include "game/part.hpp"
#include "game/accessory.hpp"
#include "game/camshaft.hpp"
#include "game/charger.hpp"
#include "game/clutch.hpp"
#include "game/cooler.hpp"
#include "game/cylinderhead.hpp"
#include "game/differential.hpp"
#include "game/engine.hpp"
#include "game/exhaustmanifold.hpp"
#include "game/exhaustpipe.hpp"
#include "game/fuelintake.hpp"
#include "game/fuelpump.hpp"
#include "game/injector.hpp"
#include "game/intakemanifold.hpp"
#include "game/tire.hpp"
#include "game/transmission.hpp"

#include "utils/directory.hpp"

class CheatDetectedException
{

};

class Connection
{
	public:
		bool readFromClient(ClientSocket* socket);
		
		const Player& getPlayerInfo();		
		void setPlayerInfo(const Player& playerinfo);	

		Connection();
		
	private:
		template<typename T>
		void loadPartsFromDirectory(const std::string& directory);
		template<typename T>
		bool writePartToPacket(Packet& packet,Part* part,uint16_t type_id);
	
		Player player;
		
		std::map<int,Vehicle> carshopVehicles;
		std::map<int,Vehicle> playerVehicles;
		std::map<int,std::tr1::shared_ptr<Part> > partshopParts;
	
		std::string receiveBuffer;		
		static const int BUFFER_SIZE=512;		
		char buffer[BUFFER_SIZE];
};

template<typename T>
void Connection::loadPartsFromDirectory(const std::string& directory)
{
	std::vector<std::string> files;
	std::vector<std::string>::iterator i;
	
	files=readDirectory(directory);
	
	int id;
	
	if(partshopParts.rbegin()==partshopParts.rend())
		id=0;
	else
		id=partshopParts.rbegin()->first;
	
	for(i=files.begin();i!=files.end();++i)
	{
		T* part=new T;
		
		std::tr1::shared_ptr<Part> ptr(part);		

		if(part->load(directory + (*i)))
		{
			partshopParts[id++]=ptr;
		}
	}
}

template<typename T>
bool Connection::writePartToPacket(Packet& packet,Part* part,uint16_t type_id)
{
	T* ptr=dynamic_cast<T*>(part);
					
	if(ptr)
	{
		packet<<type_id;
		packet<<*ptr;
		
		return true;
	}
	
	return false;
}

#endif // CONNECTION_HPP

