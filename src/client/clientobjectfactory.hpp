#ifndef CLIENT_OBJECTFACTORY_HPP
#define CLIENT_OBJECTFACTORY_HPP

#include "game/objectfactory.hpp"

namespace Client
{

class Connection;

class ObjectFactory : public Game::ObjectFactory
{
	public:
		ObjectFactory(Connection& connection);

	protected:
		virtual Game::Object* allocate(const Json::Value&);

	private:
		Connection& connection;
};

}

#endif
