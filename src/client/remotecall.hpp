#ifndef CLIENT_REMOTECALL_H
#define CLIENT_REMOTECALL_H

#include "game/objectidmapper.hpp"
#include "json/json.h"

class RemoteCall
{
	public:
		template<typename T>
		void addArgument(std::string name, const T& argument)
		{
			value[name] = argument;
		}

		void addArgument(std::string name, const Game::Object& object)
		{
			value[name] = objectIdMapper.getId(&object);
		}

		template<typename T>
		T getArgument(std::string name)
		{
			T argument =
		}

		RemoteCall(Game::ObjectIdMapper& objectIdMapper);

	private:
		Game::ObjectIdMapper& objectIdMapper;

		Json::Value value;
};

#endif
