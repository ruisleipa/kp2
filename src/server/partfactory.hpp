#ifndef SERVER_PARTFACTORY_HPP
#define SERVER_PARTFACTORY_HPP

#include "part.hpp"

class PartFactory
{
	public:
		Part* loadPart(const std::string& filename);

};

#endif
