#ifndef CONNECTION_HPP
#define CONNECTION_HPP

#include <string>
#include <vector>
#include <map>
#include <tr1/memory>
#include <tr1/functional>

#include "protocol/protocol.hpp"
#include "net/clientsocket.hpp"
#include "events/eventlistener.hpp"

class Packet;

const int BUFFERSIZE=512;

class Connection
{
	public:				
		bool connect(std::string hostname,int port);
		bool startLocalServer();		
		
		void processMessages();
		
		void addEventHandler(std::tr1::function<void(Connection&)> handler);
		void addEventListener(EventListener* listener);
		void removeEventListener(EventListener* listener);
		
		Connection();
		
		const Protocol::PlayerInfo& getPlayerInfo();
		const Protocol::Players& getPlayers();
		const Protocol::ShopVehicles& getShopVehicles();
		const Protocol::ShopParts& getShopParts();
		const Protocol::PlayerVehicles& getPlayerVehicles();
		const Protocol::PlayerParts& getPlayerParts();
		const Protocol::PerformanceData& getPerformanceData();
		
		void setName(const std::string& name);
		
		void buyVehicle(const std::string& id);
		void buyPart(const std::string& id);		
		
		void setActiveVehicleId(int vehiceId);
		int getActiveVehicleId();

		void updatePerformanceData();
		
		void addMachining(int vehiclePartId,const std::string& machiningId);
		void installPart(int partId);
		void uninstallPart(int vehiclePartId);
		
		void startTestRun();
		void sendControlState(const Protocol::ControlState& state);
		void quitSimulation();
		
	private:
		void propagateEvent(Event* event);
	
		void writeToServer(const Packet& packet);

		std::vector<std::tr1::function<void(Connection&)> > eventHandlers;
		
		std::set<EventListener*> listeners;
		
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
		Protocol::PerformanceData performanceData;
		
		bool eventPropagatedInNewWay;
};

#endif

