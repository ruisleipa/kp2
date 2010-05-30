#ifndef __CONNECTION_HPP
#define __CONNECTION_HPP

#include <string>

class Connection
{
	public:
		static Connection& getInstance();
		
		void connect(std::string hostname,int port);

	private:
		
		Connection();
};

#endif

