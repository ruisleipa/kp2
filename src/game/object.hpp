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
		Object() = default;
		Object(const Object&) = default;
		Object(const Json::Value&);
};

};

#endif
