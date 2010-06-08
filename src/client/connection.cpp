#include "connection.hpp"

#include <iostream>

void Connection::connect(std::string hostname,int port)
{
	m_socket.open(hostname,port);
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
		std::map<int,MessageHandler*>::iterator i;
		
		i=Connection::m_handlers.find(type);
		
		if(i!=Connection::m_handlers.end())
		{
			/*
			There is an handler for the packet type. We create a
			buffers for the packet and we pass the 
			buffers by reference to the handler.
			*/			
			Packet packet(m_receive_buffer.substr(4,length-4));
			
			try		
			{	
				(*i).second->process(packet);
			}
			catch(EndOfDataException)
			{
				std::cerr<<"Malformed packet of type "<<type<<std::endl;
			}
		}
		
		/*
		After the packet has been handled, it is removed from the
		receive buffer.
		*/
		m_receive_buffer.erase(0,length);
	}
}

void Connection::writeToServer(const char* data,int size)
{
	m_send_buffer.append(data,size);
}

void Connection::addMessageHandler(uint16_t id,MessageHandler* handler)
{
	Connection::m_handlers[id]=handler;
}


