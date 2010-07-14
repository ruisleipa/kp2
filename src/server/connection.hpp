#ifndef CONNECTION_HPP
#define CONNECTION_HPP

#include <stdint.h>
#include <map>
#include <string>
#include <vector>

#include "shared/clientsocket.hpp"
#include "shared/player.hpp"
#include "shared/vehicle.hpp"

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
		Player m_player;
		
		std::vector<Vehicle> m_carshop_vehicles;
		std::vector<Vehicle> m_player_vehicles;		
	
		std::string m_receive_buffer;		
		static const int BUFFER_SIZE=512;		
		char m_buffer[BUFFER_SIZE];
};

#endif // CONNECTION_HPP

