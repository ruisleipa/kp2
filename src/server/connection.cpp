#include "connection.hpp"

#include <sstream>
#include <algorithm>
#include <iostream>

std::map<int,Command*> Connection::m_commands;

void Connection::readFromClient(char* data,int size)
{
	m_receive_buffer.append(data,size);
	
	uint16_t length;
	uint16_t type;
	
	while(m_receive_buffer.size()>=4)
	{
		/*
		We have a headerful of data in the buffer. Now we need to check
		if there is a complete packet in the buffer. The size of the
		packet is in the header, so we check the size with the value
		from the header.
		*/		
		m_receive_buffer.copy((char*)&length,sizeof(length));
		m_receive_buffer.copy((char*)&type,sizeof(type),2);	
	
		length=ntohs(length);
		type=ntohs(type);
	
		/*
		If there is no enough data we quit the loop.
		*/
		if(m_receive_buffer.size()<length)
			break;	
	
		std::cout<<"cmd len: "<<length<<" type: "<<type<<std::endl;
	
		/*
		There was a complete packet in the buffer. Now we give the 
		packet to the appropriate handler object. The handler object is 
		fetched by the type field in the packet header.
		*/			
		std::map<int,Command*>::iterator i;
		
		i=Connection::m_commands.find(type);
		
		if(i!=Connection::m_commands.end())
		{
			/*
			There is an handler for the packet type. We create
			buffers for the packet and the response. We pass the 
			buffers by reference to the handler.
			*/			
			Packet packet(m_receive_buffer.substr(4,length-4));
			
			Packet response;
			
			try		
			{	
				(*i).second->process(packet,response);
			}
			catch(EndOfDataException)
			{
				std::cerr<<"Malformed packet of type "<<type<<std::endl;
				m_receive_buffer.erase(0,length);
				continue;
			}			
			
			/*
			After handling, a packet header is appended to the
			send buffer. Then the buffer is appended to the send
			buffer for sending back to he client.
			*/
			std::string responsestr=response.getString();
			
			uint16_t len=htons((uint16_t)(responsestr.size()+4));
						
			m_send_buffer.append((char*)&len,sizeof(len));
			m_send_buffer.append((char*)&type,sizeof(type));	
			m_send_buffer+=response.getString();
		}
		
		/*
		After the packet has been handled, it is removed from the
		receive buffer.
		*/
		m_receive_buffer.erase(0,length);
	}
}

void Connection::writeToClient(ClientSocket* socket)
{
	int written;

	while((written=socket->write(m_send_buffer.c_str(),m_send_buffer.size()))>0)
	{
		m_send_buffer.erase(0,written);
	}
}

void Connection::addCommand(uint16_t id,Command* command)
{
	Connection::m_commands[id]=command;
}



