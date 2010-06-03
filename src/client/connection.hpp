#ifndef __CONNECTION_HPP
#define __CONNECTION_HPP

#include <string>
#include <map>

#include "shared/clientsocket.hpp"
#include "messagehandler.hpp"

const int BUFFERSIZE=512;

class Connection
{
	public:
		static Connection& getInstance();
		
		void connect(std::string hostname,int port);
		
		void addMessageHandler(uint16_t id,MessageHandler* handler);
		
		void writeToServer(const char* data,int size);
		
		void processMessages();

	private:
		Connection();
		
		std::map<int,MessageHandler*> m_handlers;
		
		ClientSocket m_socket;
		
		std::string m_receive_buffer;
		std::string m_send_buffer;
						
		char m_buffer[BUFFERSIZE];
};

#endif

