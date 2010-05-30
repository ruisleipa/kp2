#include "connection.hpp"

#include <iostream>
#include "sdl.hpp"

Connection& Connection::getInstance()
{
	static Connection instance;
	
	return instance;
}

void Connection::connect(std::string hostname,int port)
{
	std::cout<<hostname<<" "<<port<<std::endl;
}

Connection::Connection()
{
	Sdl::getInstance();
}

