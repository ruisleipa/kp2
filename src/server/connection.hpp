#ifndef CONNECTION_HPP
#define CONNECTION_HPP

#include <stdint.h>
#include <map>
#include <string>
#include <vector>

#include <tr1/memory>

#include "shared/clientsocket.hpp"
#include "shared/player.hpp"
#include "shared/vehicle.hpp"

#include "shared/part.hpp"
#include "shared/accessory.hpp"
#include "shared/camshaft.hpp"
#include "shared/charger.hpp"
#include "shared/clutch.hpp"
#include "shared/cooler.hpp"
#include "shared/cylinderhead.hpp"
#include "shared/differential.hpp"
#include "shared/engine.hpp"
#include "shared/exhaustmanifold.hpp"
#include "shared/exhaustpipe.hpp"
#include "shared/fuelintake.hpp"
#include "shared/fuelpump.hpp"
#include "shared/injector.hpp"
#include "shared/intakemanifold.hpp"
#include "shared/tire.hpp"
#include "shared/transmission.hpp"

#include "shared/directory.hpp"

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
	
		Player m_player;
		
		std::map<int,Vehicle> m_carshop_vehicles;
		std::map<int,Vehicle> m_player_vehicles;
		std::map<int,std::tr1::shared_ptr<Part> > m_partshop_parts;
	
		std::string m_receive_buffer;		
		static const int BUFFER_SIZE=512;		
		char m_buffer[BUFFER_SIZE];
};

template<typename T>
void Connection::loadPartsFromDirectory(const std::string& directory)
{
	std::vector<std::string> files;
	std::vector<std::string>::iterator i;
	
	files=readDirectory(directory);
	
	int id;
	
	if(m_partshop_parts.rbegin()==m_partshop_parts.rend())
		id=0;
	else
		id=m_partshop_parts.rbegin()->first;
	
	for(i=files.begin();i!=files.end();++i)
	{
		T* part=new T;
		
		std::tr1::shared_ptr<Part> ptr(part);		

		if(part->load(directory + (*i)))
		{
			m_partshop_parts[id++]=ptr;
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

