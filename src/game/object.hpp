#ifndef GAME_OBJECT_HPP
#define GAME_OBJECT_HPP

#include "serializable.hpp"

#ifdef KP2_CLIENT
#include <QObject>
#endif

namespace Game
{

#ifdef KP2_CLIENT

class ObjectSignals : public QObject
{
	Q_OBJECT
	
	signals:
		void changed();
};

#else

class ObjectSignals
{
	protected:
		void changed(){};
};

#endif

class Object : public ObjectSignals, public Serializable
{
	public:
		template<class T>
		static T* clone(const T* t)
		{
			Json::Value v;
			
			t->save(v);
			
			return new T(v);
		};
		
		Object() = default;
		Object(const Object&) = default;
		Object(const Json::Value&);

};

};

#endif
