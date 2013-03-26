#ifndef CLIENT_OBJECTFACTORY_HPP
#define CLIENT_OBJECTFACTORY_HPP

#include "game/objectfactory.hpp"
#include "game/objectidmapper.hpp"

namespace Client
{

class Connection;

class ObjectFactory : public Game::ObjectFactory
{
	public:
		Game::Object* deserialize(const Json::Value& serializedObject);

		ObjectFactory(Connection& connection, Game::ObjectIdMapper& objectIdMapper);

	protected:
		virtual Game::Object* allocate(const Json::Value&);

	private:
		Connection& connection;
		Game::ObjectIdMapper& objectIdMapper;
};

}

#endif
