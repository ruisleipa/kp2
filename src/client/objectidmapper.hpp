#ifndef CLIENT_OBJECTIDMAPPER_HPP
#define CLIENT_OBJECTIDMAPPER_HPP

#include "game/objectidmapper.hpp"

namespace Client
{

class ObjectIdMapper : public Game::ObjectIdMapper
{
	protected:
		std::string getLocalIdPrefix();

};

}

#endif
