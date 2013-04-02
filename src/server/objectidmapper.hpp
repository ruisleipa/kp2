#ifndef SERVER_OBJECTIDMAPPER_HPP
#define SERVER_OBJECTIDMAPPER_HPP

#include "game/objectidmapper.hpp"

namespace Server
{

class ObjectIdMapper : public Game::ObjectIdMapper
{
	protected:
		std::string getLocalIdPrefix();
};

}

#endif
