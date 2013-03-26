#ifndef GAME_OBJECTFACTORY_HPP
#define GAME_OBJECTFACTORY_HPP

#include "json/value.h"
#include "object.hpp"
#include "objectidmapper.hpp"

namespace Game
{

class ObjectFactory
{
	public:
		virtual Object* deserialize(const Json::Value&);

		template<class T>
		T* clone(const T* t)
		{
			Json::Value v;

			t->save(v);

			return dynamic_cast<T*>(deserialize(v));
		};

	protected:
		virtual Object* allocate(const Json::Value&);

	private:
		Object* create(const Json::Value& value);

};

};

#endif
