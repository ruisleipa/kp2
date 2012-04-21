#ifndef SERVER_OBJECTFACTORY_HPP
#define SERVER_OBJECTFACTORY_HPP

#include "game/objectfactory.hpp"

class ServerObjectFactory : public Game::ObjectFactory
{
	protected:
		virtual Game::Object* allocate(const Json::Value&);

};

#endif
