#ifndef GAME_OBJECTFACTORY_HPP
#define GAME_OBJECTFACTORY_HPP

#include "json/value.h"
#include "object.hpp"

namespace Game
{

class ObjectFactory
{
	public:
		Object* create(const Json::Value&);

		template<class T>
		T* clone(const T* t)
		{
			Json::Value v;

			t->save(v);

			return dynamic_cast<T*>(create(v));
		};

	protected:
		virtual Object* allocate(const Json::Value&);
};

};

#endif
