#ifndef SERVER_PARTMODELFACTORY_HPP
#define SERVER_PARTMODELFACTORY_HPP

#include "partmodel.hpp"

class PartModelFactory
{
	public:
		PartModel* loadPartModel(const std::string& filename);

};

#endif
