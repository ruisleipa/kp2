#ifndef CONNECTION_HPP
#define CONNECTION_HPP

#include <string>
#include <vector>
#include <map>
#include <tr1/memory>
#include <tr1/functional>

#include "net/clientsocket.hpp"
#include "net/protocol.hpp"

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

#include "events/eventlistener.hpp"
#include "sounds/sound.hpp"

const int BUFFERSIZE=512;

class Connection
{
	public:				
		bool connect(std::string hostname,int port);
		bool startLocalServer();		
		
		void processMessages();
		
		void addEventHandler(std::tr1::function<void(Connection&)> handler);
		
		Connection();
		
		void writeToServer(const Packet& packet);
		
		void setName(const std::string& name);
		const std::string& getName() const;
		int getMoney() const;
		
		void buyCar(int index);
		
		int getCarshopVehicleMaxId() const;
		bool getCarshopVehicle(int index,Vehicle& vehicle) const;
		
		int getPlayerVehicleMaxId() const;		
		bool getPlayerVehicle(int index,Vehicle& vehicle) const;		
		
		int getPartshopPartMaxId() const;		
		bool getPartshopPart(int index,Part& part) const;		
		template<typename T>
		bool getPartshopPartOfType(int index,Part& part) const;
		template<typename T>
		bool getPartshopPartOfTypeSubtyped(int index,T& part) const;	
		
	private:
		template<typename T>
		std::tr1::shared_ptr<Part> getPartFromPacket(Packet& packet);
	
		/*
		Connection data.
		*/
		std::string m_name;
		int m_money;
		
		std::map<int,Vehicle> m_carshop_vehicles;
		std::map<int,Vehicle> m_player_vehicles;
		std::map<int,std::tr1::shared_ptr<Part> > m_partshop_parts;
	
		/*
		Event handling variables.
		*/
		std::vector<std::tr1::function<void(Connection&)> > eventHandlers;

		
		Sound m_cash;
		
		/*
		Networking variables.
		*/
		ClientSocket m_socket;
		
		std::string m_receive_buffer;
		std::string m_send_buffer;						
		char buffer[BUFFERSIZE];
};

template<typename T>
bool Connection::getPartshopPartOfType(int index,Part& part) const
{
	std::map<int,std::tr1::shared_ptr<Part> >::const_iterator i;
	
	i=m_partshop_parts.find(index);
	
	if(i==m_partshop_parts.end())
	{
		return false;
	}
	
	T* ptr=dynamic_cast<T*>(i->second.get());
	
	if(!ptr)
		return false;
	
	part=*((*i).second.get());
	
	return true;
}

template<typename T>
bool Connection::getPartshopPartOfTypeSubtyped(int index,T& part) const
{
	std::map<int,std::tr1::shared_ptr<Part> >::const_iterator i;
	
	i=m_partshop_parts.find(index);
	
	if(i==m_partshop_parts.end())
	{
		return false;
	}
	
	T* ptr=dynamic_cast<T*>(i->second.get());
	
	if(!ptr)
		return false;	
	
	part=*ptr;
	
	return true;
}

template<typename T>
std::tr1::shared_ptr<Part> Connection::getPartFromPacket(Packet& packet)
{
	T* part=new T;
						
	std::tr1::shared_ptr<Part> ptr(part);
	
	packet>>(*part);

	return ptr;
}

#endif

