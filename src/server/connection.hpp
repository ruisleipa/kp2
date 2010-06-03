#ifndef __CONNECTION_HPP
#define __CONNECTION_HPP

#include <stdint.h>
#include <map>
#include <string>

#include "shared/clientsocket.hpp"
#include "command.hpp"

class Connection
{
	public:
		void readFromClient(char* data,int size);
		void writeToClient(ClientSocket* socket);
		
		static void addCommand(uint16_t id,Command* command);
		
	private:
		static std::map<int,Command*> m_commands;
	
		std::string m_receive_buffer;
		std::string m_send_buffer;
};

#endif // __CONNECTION_HPP

