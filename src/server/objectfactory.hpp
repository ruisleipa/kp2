#ifndef SERVER_OBJECTFACTORY_HPP
#define SERVER_OBJECTFACTORY_HPP

#include "game/objectfactory.hpp"
#include "game/objectidmapper.hpp"

namespace Server
{

class ObjectFactory : public Game::ObjectFactory
{
	public:
		Game::Object* deserialize(const Json::Value& serializedObject);

		ObjectFactory(Game::ObjectIdMapper& objectIdMapper);

	private:
		Game::ObjectIdMapper& objectIdMapper;
};

}

#endif
