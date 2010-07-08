#include "connection.hpp"

#include <iostream>

#include "shared/inifile.hpp"
#include "shared/packet.hpp"
#include "sound.hpp"

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
	while((read=m_socket.read(m_buffer,BUFFERSIZE))>0)
	{
		std::cout<<"Got "<<read<<" bytes."<<std::endl;

		m_receive_buffer.append(m_buffer,read);
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
		std::cout<<"Written "<<written<<" bytes."<<std::endl;

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
					Vehicle vehicle;
					message>>vehicle;
					
					m_carshop_vehicles.push_back(vehicle);				
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
					Vehicle vehicle;
					message>>vehicle;
					
					m_player_vehicles.push_back(vehicle);				
				}					
			}	
			
			m_event_listener->doConnectionEvent(*this);
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

std::vector<Vehicle> Connection::getCarshopVehicles() const
{
	return m_carshop_vehicles;
}

std::vector<Vehicle> Connection::getPlayerVehicles() const
{
	return m_player_vehicles;
}

void Connection::writeToServer(const Packet& packet)
{
	std::string str=packet.getString();

	m_send_buffer.append(str.c_str(),str.size());
}

void Connection::setEventListener(EventListener* event_listener)
{
	m_event_listener=event_listener;
}

void Connection::addMessageHandler(uint16_t id,MessageHandler* handler)
{
	Connection::m_handlers[id]=handler;
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

Connection::Connection():
	m_event_listener(&m_default_listener)
{

	m_cash.load("data/sounds/kassa.wav");
}		
