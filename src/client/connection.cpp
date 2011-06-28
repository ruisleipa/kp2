#include "connection.hpp"

#include <iostream>
#include <stdint.h>

#include "utils/inifile.hpp"
#include "utils/string.hpp"
#include "net/packet.hpp"
#include "net/clientsocket.hpp"
#include "protocol/protocol.hpp"

#include "protocol/setname.hpp"
#include "protocol/buyvehicle.hpp"
#include "protocol/buypart.hpp"
#include "protocol/setactivevehicle.hpp"
#include "protocol/installpart.hpp"
#include "protocol/uninstallpart.hpp"

#include "simulationstartevent.hpp"
#include "simulationvehicledataevent.hpp"
#include "simulationvehiclestateevent.hpp"
#include "simulationvehicleresultevent.hpp"
#include "vehicleerrorevent.hpp"
#include "installerrorevent.hpp"
#include "connectionlostevent.hpp"

#include "utils/sdl.hpp"

#ifdef WIN32
#include <windows.h>
#endif

bool Connection::connect(std::string hostname,int port)
{
	if(!socket.connect(hostname,port))
		return false;

	return true;
}

void Connection::processMessages()
{	
	int read,written;

	while((read=socket.read(scrapBuffer,BUFFERSIZE))>0)
	{
		receiveBuffer.append(scrapBuffer,read);
	}
			
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
		
		eventPropagatedInNewWay = false;
		
		try
		{
			std::cout << "RECEIVING" << std::endl << message << std::endl;
		
			if(message.getType() == Protocol::DATA_PLAYER_INFO)
			{
				message >> playerInfo;
			}
			else if(message.getType() == Protocol::DATA_ACTIVE_VEHICLE_ID)
			{
				message >> activeVehicleId;
			}
			else if(message.getType() == Protocol::DATA_PLAYERS)
			{
				message >> players;
			}
			else if(message.getType() == Protocol::DATA_SHOP_VEHICLES)
			{
				message >> shopVehicles;
			}
			else if(message.getType() == Protocol::DATA_SHOP_PARTS)
			{
				message >> shopParts;
			}
			else if(message.getType() == Protocol::DATA_PLAYER_VEHICLES)
			{
				message >> playerVehicles;
			}
			else if(message.getType() == Protocol::DATA_PLAYER_PARTS)
			{
				message >> playerParts;
			}
			else if(message.getType() == Protocol::DATA_INSTALL_ERROR)
			{
				std::string error;
			
				message >> error;
#ifdef WIN32
				std::wstring errorMessage = convertToWideString(error);
				
				const WCHAR* errorCaption=L"Kiihdytyspeli 2";
				
				MessageBoxW(NULL, (const WCHAR*)errorMessage.c_str(), errorCaption, MB_OK | MB_ICONINFORMATION | MB_TASKMODAL);
#else			
				std::cout << error;
#endif			
			}
			else if(message.getType() == Protocol::DATA_PERFORMANCE)
			{
				message >> performanceData;
			}
			else if(message.getType() == Protocol::DATA_SIMULATION_START)
			{
				SimulationStartEvent event;
				
				propagateEvent(&event);
			}
			else if(message.getType() == Protocol::DATA_SIMULATION_VEHICLE_DATA)
			{
				Protocol::SimulationVehicleData data;
				
				message >> data;
				
				SimulationVehicleDataEvent event;
				event.data = data;
				
				propagateEvent(&event);
			}
			else if(message.getType() == Protocol::DATA_SIMULATION_VEHICLE_STATE)
			{
				Protocol::SimulationVehicleState state;
				
				message >> state;
				
				SimulationVehicleStateEvent event;
				event.state = state;
				
				propagateEvent(&event);
			}
			else if(message.getType() == Protocol::DATA_SIMULATION_VEHICLE_RESULT)
			{
				Protocol::SimulationVehicleResult result;
				
				message >> result;
				
				SimulationVehicleResultEvent event;
				event.result = result;
				
				propagateEvent(&event);
			}
			
			if(eventPropagatedInNewWay == false)
			{
				std::vector<std::tr1::function<void(Connection&)> >::iterator i;
				
				for(i=eventHandlers.begin();i!=eventHandlers.end();++i)
				{
					(*i)(*this);
				}
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

const Protocol::PlayerInfo& Connection::getPlayerInfo()
{
	return playerInfo;
}

const Protocol::Players& Connection::getPlayers()
{
	return players;
}

const Protocol::ShopVehicles& Connection::getShopVehicles()
{
	return shopVehicles;
}

const Protocol::ShopParts& Connection::getShopParts()
{
	return shopParts;
}

const Protocol::PlayerVehicles& Connection::getPlayerVehicles()
{
	return playerVehicles;
}

const Protocol::PlayerParts& Connection::getPlayerParts()
{
	return playerParts;
}

const Protocol::PerformanceData& Connection::getPerformanceData()
{
	return performanceData;
}

void Connection::setName(const std::string& name)
{
	Packet packet;
	
	packet.setType(Protocol::COMMAND_SET_NAME);
	
	Protocol::SetName setName;
	setName.name = name;
	
	packet << setName;
	
	writeToServer(packet);
}

void Connection::buyVehicle(const std::string& id)
{
	Packet packet;
	
	packet.setType(Protocol::COMMAND_BUY_VEHICLE);
	
	Protocol::BuyVehicle buyVehicle;
	buyVehicle.id = id;
	
	packet << buyVehicle;
	
	writeToServer(packet);
}

void Connection::buyPart(const std::string& id)
{
	Packet packet;
	
	packet.setType(Protocol::COMMAND_BUY_PART);
	
	Protocol::BuyPart buyPart;
	buyPart.id = id;
	
	packet << buyPart;
	
	writeToServer(packet);
}		

void Connection::setActiveVehicleId(int vehiceId)
{
	Packet packet;
	
	packet.setType(Protocol::COMMAND_SET_ACTIVE_VEHICLE_ID);
	
	Protocol::SetActiveVehicle command;
	command.id = vehiceId;
	
	packet << command;
	
	writeToServer(packet);
}

int Connection::getActiveVehicleId()
{
	return activeVehicleId;
}

void Connection::addMachining(int vehiclePartId,const std::string& machiningId)
{

}

void Connection::installPart(int partId)
{
	Packet packet;
	
	packet.setType(Protocol::COMMAND_INSTALL_PART);
	
	Protocol::InstallPart command;
	command.id = partId;
	
	packet << command;
	
	writeToServer(packet);
}

void Connection::uninstallPart(int vehiclePartId)
{
	Packet packet;
	
	packet.setType(Protocol::COMMAND_UNINSTALL_PART);
	
	Protocol::UninstallPart command;
	command.id = vehiclePartId;
	
	packet << command;
	
	writeToServer(packet);
}

void Connection::updatePerformanceData()
{
	Packet packet;
	
	packet.setType(Protocol::COMMAND_UPDATE_PERFORMANCE);
	
	writeToServer(packet);
}

void Connection::startTestRun()
{
	Packet packet;
	
	packet.setType(Protocol::COMMAND_TESTRUN_START);
	
	writeToServer(packet);
}

void Connection::sendControlState(const Protocol::ControlState& state)
{
	Packet packet;
	
	packet.setType(Protocol::COMMAND_CONTROL_STATE);
	
	packet << state;
	
	writeToServer(packet);
}

void Connection::propagateEvent(Event* event)
{
	std::vector<EventListener*>::iterator i;

	for(i = listeners.begin(); i != listeners.end(); ++i)
	{
		(*i)->handleEvent(event);
	}
	
	eventPropagatedInNewWay = true;
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

void Connection::addEventListener(EventListener* listener)
{
	listeners.push_back(listener);
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

Connection::Connection():
	activeVehicleId(0),
	eventPropagatedInNewWay(false)
{
	
}		
