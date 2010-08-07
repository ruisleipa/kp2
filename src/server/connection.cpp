#include "connection.hpp"

#include "shared/packet.hpp"
#include "shared/protocol.hpp"

#include <sstream>
#include <algorithm>
#include <iostream>
#include <limits>

bool Connection::readFromClient(ClientSocket* socket)
{
	int read;

	/*
	Read as long as there is data to read (reads more than
	zero bytes).
	*/
	while((read=socket->read(m_buffer,BUFFER_SIZE))>0)
	{
		m_receive_buffer.append(m_buffer,read);
	}
	
	/*
	ClientSocket::read returns -1 when the connection has
	been closed. We signal this to our caller.
	*/
	if(read==-1)
	{
		return false;
	}
	
	while(1)
	{
		Packet request;
	
		try
		{
			request.readFromBuffer(m_receive_buffer);
		}
		catch(EndOfDataException)
		{
			/*
			We don't have enough data for a packet, so we return.
			*/
			return true;			
		}
		
		Packet response;	
		
		try
		{			
			uint16_t type=request.getType();
			
			std::cout<<(int)type<<std::endl;
			
			if(type==PLAYER_NAME)
			{
				//TODO: do duplicate name checking
				std::string newname;
				request>>newname;
				
				m_player.setName(newname);
				
				response.setType(PLAYER_NAME);
				response<<m_player.getName();
			}
			else if(type==PLAYER_MONEY)
			{
				response.setType(PLAYER_MONEY);
				response<<int32_t(m_player.getMoney());
			}
			else if(type==CARSHOP_LIST)
			{
				response.setType(CARSHOP_LIST);
				
				std::map<int,Vehicle>::iterator i;
				
				response<<uint32_t(m_carshop_vehicles.size());
				
				for(i=m_carshop_vehicles.begin();i!=m_carshop_vehicles.end();++i)
				{
					response<<uint32_t(i->first);
					response<<i->second;
				}				
			}
			else if(type==CARSHOP_BUY)
			{
				uint32_t carindex;
				
				request>>carindex;
				
				std::map<int,Vehicle>::iterator i;
				
				i=m_carshop_vehicles.find(carindex);
					
				if(i==m_carshop_vehicles.end())
					continue;
					
				response.setType(CARSHOP_BUY);
				
				if(m_player.changeMoney(-1000))
				{
					std::map<int,Vehicle>::iterator i;
					
					for(int id=0;id<std::numeric_limits<int>::max();id++)
					{
						i=m_player_vehicles.find(id);
					
						if(i!=m_player_vehicles.end())
							continue;
							
						m_player_vehicles[id]=m_carshop_vehicles[carindex];
						
						break;
					}
					
					response<<uint32_t(0);
				}
				else
				{
					response<<uint32_t(1);
				}		
			}
			else if(type==GARAGE_LIST)
			{
				response.setType(GARAGE_LIST);
				
				std::map<int,Vehicle>::iterator i;
				
				response<<uint32_t(m_player_vehicles.size());
				
				for(i=m_player_vehicles.begin();i!=m_player_vehicles.end();++i)
				{
					response<<uint32_t(i->first);
					response<<i->second;
				}				
			}
			else if(type==PARTSHOP_LIST)
			{
				response.setType(PARTSHOP_LIST);
				
				std::map<int,std::tr1::shared_ptr<Part> >::iterator i;
				
				response<<uint32_t(m_partshop_parts.size());
				
				for(i=m_partshop_parts.begin();i!=m_partshop_parts.end();++i)
				{
					response<<uint32_t(i->first);
					
					Part* part=i->second.get();
										
					/*
					Try to send the part in every type.
					When the correct type is found, short-
					circuiting will stop the evaluation.
					*/					
					
					bool typefound=
					(	
						writePartToPacket<Accessory>(response,part,PART_TYPE_ID_ACCESSORY) ||
						writePartToPacket<Camshaft>(response,part,PART_TYPE_ID_CAMSHAFT) ||
						writePartToPacket<Charger>(response,part,PART_TYPE_ID_CHARGER) ||
						writePartToPacket<Clutch>(response,part,PART_TYPE_ID_CLUTCH) ||
						writePartToPacket<Cooler>(response,part,PART_TYPE_ID_COOLER) ||
						writePartToPacket<CylinderHead>(response,part,PART_TYPE_ID_CYLINDERHEAD) ||
						writePartToPacket<Differential>(response,part,PART_TYPE_ID_DIFFERENTIAL) ||
						writePartToPacket<Engine>(response,part,PART_TYPE_ID_ENGINE) ||
						writePartToPacket<ExhaustManifold>(response,part,PART_TYPE_ID_EXHAUSTMANIFOLD) ||
						writePartToPacket<ExhaustPipe>(response,part,PART_TYPE_ID_EXHAUSTPIPE) ||
						writePartToPacket<FuelIntake>(response,part,PART_TYPE_ID_FUELINTAKE) ||
						writePartToPacket<FuelPump>(response,part,PART_TYPE_ID_FUELPUMP) ||
						writePartToPacket<Injector>(response,part,PART_TYPE_ID_INJECTOR) ||
						writePartToPacket<IntakeManifold>(response,part,PART_TYPE_ID_INTAKEMANIFOLD) ||
						writePartToPacket<Tire>(response,part,PART_TYPE_ID_TIRE) ||
						writePartToPacket<Transmission>(response,part,PART_TYPE_ID_TRANSMISSION)
					);
				}

				for(i=m_partshop_parts.begin();i!=m_partshop_parts.end();++i)
				{
					Part* part=i->second.get();
					
					std::cout<<part->getName()<<" "<<part->getPrice()<<std::endl;
				}					
			}	
			else
			{
				continue;
			}
		}
		catch(EndOfDataException)
		{
			std::cerr<<"Invalid packet!"<<std::endl;
			std::cerr<<request<<std::endl;		
			return false;
		}		
		
		std::string responsestr=response.getString();
	
		socket->write(responsestr.c_str(),responsestr.size());	
	}
	
	return true;
}

Connection::Connection()
{
	std::vector<std::string> files;
	std::vector<std::string>::iterator i;
	
	files=readDirectory("gamedata/vehicles/","cfg");
	
	int id=0;
	
	for(i=files.begin();i!=files.end();++i)
	{
		Vehicle vehicle;
		
		if(vehicle.load("gamedata/vehicles/" + (*i)))
		{
			m_carshop_vehicles[id++]=vehicle;
		}
	}
	
	loadPartsFromDirectory<Accessory>("gamedata/parts/accessories/");
	loadPartsFromDirectory<Camshaft>("gamedata/parts/camshafts/");
	loadPartsFromDirectory<Charger>("gamedata/parts/chargers/");
	loadPartsFromDirectory<Clutch>("gamedata/parts/clutches/");
	loadPartsFromDirectory<Cooler>("gamedata/parts/coolers/");
	loadPartsFromDirectory<CylinderHead>("gamedata/parts/cylinderheads/");
	loadPartsFromDirectory<Differential>("gamedata/parts/differentials/");
	loadPartsFromDirectory<Engine>("gamedata/parts/engines/");
	loadPartsFromDirectory<ExhaustManifold>("gamedata/parts/exhaustmanifolds/");
	loadPartsFromDirectory<ExhaustPipe>("gamedata/parts/exhaustpipes/");
	loadPartsFromDirectory<FuelIntake>("gamedata/parts/fuelintakes/");
	loadPartsFromDirectory<FuelPump>("gamedata/parts/fuelpumps/");
	loadPartsFromDirectory<Injector>("gamedata/parts/injectors/");
	loadPartsFromDirectory<IntakeManifold>("gamedata/parts/intakemanifolds/");
	loadPartsFromDirectory<Tire>("gamedata/parts/tires/");
	loadPartsFromDirectory<Transmission>("gamedata/parts/transmissions/");
}



