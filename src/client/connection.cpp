#include "connection.hpp"

#include <iostream>
#include <stdint.h>

#include "utils/inifile.hpp"
#include "net/packet.hpp"

#include "utils/sdl.hpp"

bool Connection::connect(std::string hostname,int port)
{
	return m_socket.connect(hostname,port);
}

void Connection::processMessages()
{	
	int read,written;
	
	/*
	Read as long as there is data to read (reads more than
	zero bytes).
	*/
	while((read=m_socket.read(buffer,BUFFERSIZE))>0)
	{
		m_receive_buffer.append(buffer,read);
	}
			
	/*
	ClientSocket::read returns -1 when the connection has
	been closed.
	*/
	if(read==-1)
	{
		//TODO: Handle disconnection!
	}
	
	/*
	Write as much as we can (writes more than
	zero bytes).
	*/
	while((written=m_socket.write(m_send_buffer.c_str(),m_send_buffer.size()))>0)
	{
		m_send_buffer.erase(0,written);
	}
	
	while(1)
	{
		Packet message;
	
		try
		{
			message.readFromBuffer(m_receive_buffer);
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
			uint16_t type=message.getType();
			
			if(type==PLAYER_NAME)
			{
				message>>m_name;
			}
			else if(type==PLAYER_MONEY)
			{
				int32_t money;
				message>>money;
				m_money=money;
			}
			else if(type==CARSHOP_LIST)
			{
				m_carshop_vehicles.clear();
				
				uint32_t num_cars;
				
				message>>num_cars;
				
				for(int i=0;i<num_cars;i++)
				{				
					uint32_t vehicle_id;
					
					message>>vehicle_id;
				
					Vehicle vehicle;
					message>>vehicle;
					
					m_carshop_vehicles[vehicle_id]=vehicle;	
				}				
			}
			else if(type==CARSHOP_BUY)
			{
				uint32_t success;
				
				message>>success;
				
				if(success==0)
				{
					m_cash.play();
				}
				else
				{
					
				}

				Packet packet;
				packet.setType(PLAYER_MONEY);
				writeToServer(packet);
				
				packet.setType(GARAGE_LIST);		
				writeToServer(packet);
								
			}
			else if(type==GARAGE_LIST)
			{
				m_player_vehicles.clear();
				
				uint32_t num_cars;
				
				message>>num_cars;
				
				for(int i=0;i<num_cars;i++)
				{
					uint32_t vehicle_id;
					
					message>>vehicle_id;
				
					Vehicle vehicle;
					message>>vehicle;
					
					m_player_vehicles[vehicle_id]=vehicle;						
				}					
			}
			else if(type==PARTSHOP_LIST)
			{
				m_partshop_parts.clear();
				
				uint32_t num_parts;
				
				message>>num_parts;
				
				for(int i=0;i<num_parts;i++)
				{				
					uint32_t part_id;
					uint16_t type_id;
					
					message>>part_id;
					message>>type_id;
					
					std::tr1::shared_ptr<Part> ptr;
					
					if(type_id==PART_TYPE_ID_ACCESSORY)
						ptr=getPartFromPacket<Accessory>(message);
					else if(type_id==PART_TYPE_ID_CAMSHAFT)
						ptr=getPartFromPacket<Camshaft>(message);
					else if(type_id==PART_TYPE_ID_CHARGER)
						ptr=getPartFromPacket<Charger>(message);
					else if(type_id==PART_TYPE_ID_CLUTCH)
						ptr=getPartFromPacket<Clutch>(message);
					else if(type_id==PART_TYPE_ID_COOLER)
						ptr=getPartFromPacket<Cooler>(message);
					else if(type_id==PART_TYPE_ID_CYLINDERHEAD)
						ptr=getPartFromPacket<CylinderHead>(message);
					else if(type_id==PART_TYPE_ID_DIFFERENTIAL)
						ptr=getPartFromPacket<Differential>(message);
					else if(type_id==PART_TYPE_ID_ENGINE)
						ptr=getPartFromPacket<Engine>(message);
					else if(type_id==PART_TYPE_ID_EXHAUSTMANIFOLD)
						ptr=getPartFromPacket<ExhaustManifold>(message);
					else if(type_id==PART_TYPE_ID_EXHAUSTPIPE)
						ptr=getPartFromPacket<ExhaustPipe>(message);
					else if(type_id==PART_TYPE_ID_FUELINTAKE)
						ptr=getPartFromPacket<FuelIntake>(message);
					else if(type_id==PART_TYPE_ID_FUELPUMP)
						ptr=getPartFromPacket<FuelPump>(message);
					else if(type_id==PART_TYPE_ID_INJECTOR)
						ptr=getPartFromPacket<Injector>(message);
					else if(type_id==PART_TYPE_ID_INTAKEMANIFOLD)
						ptr=getPartFromPacket<IntakeManifold>(message);
					else if(type_id==PART_TYPE_ID_TIRE)
						ptr=getPartFromPacket<Tire>(message);
					else if(type_id==PART_TYPE_ID_TRANSMISSION)
						ptr=getPartFromPacket<Transmission>(message);
					else
						continue;
						
					m_partshop_parts[part_id]=ptr;									
				}

				std::map<int,std::tr1::shared_ptr<Part> >::iterator i;
				
				for(i=m_partshop_parts.begin();i!=m_partshop_parts.end();++i)
				{
					Part* part=i->second.get();
					
					std::cout<<part->getName()<<" "<<part->getPrice()<<std::endl;
				}	
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

void Connection::setName(const std::string& name)
{
	Packet packet;
	packet.setType(PLAYER_NAME);
	packet<<name;
	
	writeToServer(packet);
}

const std::string& Connection::getName() const
{
	return m_name;
}

int Connection::getMoney() const
{
	return m_money;
}

void Connection::buyCar(int index)
{
	Packet packet;
	packet.setType(CARSHOP_BUY);
	packet<<uint32_t(index);
	
	writeToServer(packet);
}

int Connection::getCarshopVehicleMaxId() const
{
	if(m_carshop_vehicles.empty())
		return 0;
		
	return m_carshop_vehicles.rbegin()->first;
}

bool Connection::getCarshopVehicle(int index,Vehicle& vehicle) const
{
	std::map<int,Vehicle>::const_iterator i;
	
	i=m_carshop_vehicles.find(index);

	if(i == m_carshop_vehicles.end())
		return false;

	vehicle=i->second;

	return true;
}

int Connection::getPlayerVehicleMaxId() const
{
	if(m_player_vehicles.empty())
		return 0;
		
	return m_player_vehicles.rbegin()->first;
}
		
bool Connection::getPlayerVehicle(int index,Vehicle& vehicle) const
{
	std::map<int,Vehicle>::const_iterator i;
	
	i=m_player_vehicles.find(index);

	if(i == m_player_vehicles.end())
		return false;
	
	vehicle=i->second;
	
	return true;
}		

int Connection::getPartshopPartMaxId() const
{
	if(m_partshop_parts.empty())
		return 0;
		
	return m_partshop_parts.rbegin()->first;
}
		
bool Connection::getPartshopPart(int index,Part& part) const
{
	std::map<int,std::tr1::shared_ptr<Part> >::const_iterator i;
	
	i=m_partshop_parts.find(index);

	if(i == m_partshop_parts.end())
		return false;
	
	part=*(i->second.get());
	
	return true;
}

void Connection::writeToServer(const Packet& packet)
{
	std::string str=packet.getString();

	m_send_buffer.append(str.c_str(),str.size());
}

void Connection::addEventHandler(std::tr1::function<void(Connection&)> handler)
{
	eventHandlers.push_back(handler);
}

bool Connection::startLocalServer()
{
	IniFile settings;
	
	settings.setValue("Server.LocalServer",1);
	settings.setValue("Server.QuitWhenEmpty",1);	
	settings.setValue("Server.ConnectionLimit",1);

	settings.save("cfg/singleplayer.cfg");

	std::string cmd;
	std::string args="-port 31000 -config cfg/singleplayer.cfg";

#ifdef WIN32
	cmd+="start kp2_server.exe ";
	cmd+=args;
#else
	cmd+="./kp2_server ";
	cmd+=args;
	cmd+=" &";
#endif		

	system(cmd.c_str());
	
	SDL_Delay(2000);
	
	for(int i=0;i<10;i++)
	{	
		if(connect("localhost",31000))
			return true;
	}
	
	return false;
}

Connection::Connection()
{
	m_cash.load("data/sounds/kassa.wav");
}		
