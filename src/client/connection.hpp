#ifndef CONNECTION_HPP
#define CONNECTION_HPP

#include <string>
#include <vector>
#include <map>
#include <tr1/memory>
#include <tr1/functional>

#include "protocol/playerinfo.hpp"
#include "protocol/players.hpp"
#include "protocol/shopvehicles.hpp"
#include "protocol/shopparts.hpp"
#include "protocol/playervehicles.hpp"
#include "protocol/playerparts.hpp"
#include "net/clientsocket.hpp"

class Packet;

const int BUFFERSIZE=512;

class Connection
{
	public:				
		bool connect(std::string hostname,int port);
		bool startLocalServer();		
		
		void processMessages();
		
		void addEventHandler(std::tr1::function<void(Connection&)> handler);
		
		Connection();
		
		const PlayerInfo& getPlayerInfo();
		const Players& getPlayers();
		const ShopVehicles& getShopVehicles();
		const ShopParts& getShopParts();
		const PlayerVehicles& getPlayerVehicles();
		const PlayerParts& getPlayerParts();
		
		void setName(const std::string& name);
		
		void buyVehicle(const std::string& id);
		void buyPart(const std::string& id);		
		
		void setActiveVehicle(int vehiceId);
		void addMachining(int vehiclePartId,const std::string& machiningId);
		void installPart(int partId);
		void uninstallPart(int vehiclePartId);
	
	private:
		void writeToServer(const Packet& packet);

		std::vector<std::tr1::function<void(Connection&)> > eventHandlers;
		
		ClientSocket socket;
		
		std::string receiveBuffer;
		std::string sendBuffer;						
		char scrapBuffer[BUFFERSIZE];
		
		PlayerInfo playerInfo;
		Players players;
		ShopVehicles shopVehicles;
		ShopParts shopParts;
		PlayerVehicles playerVehicles;
		PlayerParts playerParts;
};

#endif

