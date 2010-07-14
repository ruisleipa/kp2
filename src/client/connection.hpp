#ifndef CONNECTION_HPP
#define CONNECTION_HPP

#include <string>
#include <vector>
#include <map>

#include "shared/clientsocket.hpp"
#include "shared/player.hpp"
#include "shared/vehicle.hpp"
#include "shared/protocol.hpp"

#include "eventlistener.hpp"
#include "sound.hpp"

const int BUFFERSIZE=512;

class Connection
{
	public:				
		bool connect(std::string hostname,int port);
		bool startLocalServer();		
		
		void processMessages();
		
		void setEventListener(EventListener* event_listener);
		
		Connection();
		
		void writeToServer(const Packet& packet);
		
		void setName(const std::string& name);
		const std::string& getName() const;
		int getMoney() const;
		
		void buyCar(int index);
		
		std::vector<Vehicle> getCarshopVehicles() const;
		std::vector<Vehicle> getPlayerVehicles() const;	
		
	private:		
		/*
		Connection data.
		*/
		std::string m_name;
		int m_money;
		
		std::vector<Vehicle> m_carshop_vehicles;
		std::vector<Vehicle> m_player_vehicles;	
	
		/*
		Event handling variables.
		*/
		EventListener* m_event_listener;		
		EventListener m_default_listener;
		
		Sound m_cash;
		
		/*
		Networking variables.
		*/
		ClientSocket m_socket;
		
		std::string m_receive_buffer;
		std::string m_send_buffer;						
		char m_buffer[BUFFERSIZE];
};

#endif

