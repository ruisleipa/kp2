#ifndef GAME_OBJECTIDMAPPER_HPP
#define GAME_OBJECTIDMAPPER_HPP

#include <string>
#include <map>

#include "object.hpp"

namespace Game
{

class ObjectIdMapper
{
	public:
		class NoIdError
		{

		};

		void addMapping(const std::string& id, const Game::Object* object);

		const std::string& getId(Object*);
		const std::string& getId(const Object*);
		Object* getObject(const std::string& id);

		template<class T>
		T getTypedObject(const std::string& id)
		{
			return dynamic_cast<T>(getObject(id));
		}

		ObjectIdMapper();

	protected:
		virtual std::string getLocalIdPrefix() = 0;

	private:
		int nextLocalId;
		std::map<Object*, std::string> idsByObject;
		std::map<std::string, Object*> objectsById;

};

}

#endif
