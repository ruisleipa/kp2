#ifndef CLIENT_OBJECTFACTORY_HPP
#define CLIENT_OBJECTFACTORY_HPP

#include "game/objectfactory.hpp"

class Connection;

class ClientObjectFactory : public Game::ObjectFactory
{
	public:
		ClientObjectFactory(Connection& connection);

	protected:
		virtual Game::Object* allocate(const Json::Value&);
		
	private:
		Connection& connection;		
};

#endif
