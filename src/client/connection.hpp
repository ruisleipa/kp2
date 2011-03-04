#ifndef CONNECTION_HPP
#define CONNECTION_HPP

#include <string>
#include <vector>
#include <map>
#include <tr1/memory>
#include <tr1/functional>

#include "protocol/protocol.hpp"
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
		
		const Protocol::PlayerInfo& getPlayerInfo();
		const Protocol::Players& getPlayers();
		const Protocol::ShopVehicles& getShopVehicles();
		const Protocol::ShopParts& getShopParts();
		const Protocol::PlayerVehicles& getPlayerVehicles();
		const Protocol::PlayerParts& getPlayerParts();
		
		void setName(const std::string& name);
		
		void buyVehicle(const std::string& id);
		void buyPart(const std::string& id);		
		
		void setActiveVehicleId(int vehiceId);
		int getActiveVehicleId();		
		
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
		
		Protocol::PlayerInfo playerInfo;
		Protocol::Players players;
		Protocol::ShopVehicles shopVehicles;
		Protocol::ShopParts shopParts;
		Protocol::PlayerVehicles playerVehicles;
		Protocol::PlayerParts playerParts;
		Protocol::VehicleId activeVehicleId;
};

#endif

