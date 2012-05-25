#ifndef GAME_OBJECT_HPP
#define GAME_OBJECT_HPP

#include "serializable.hpp"

#ifdef GAME_OBJECTS_QT
#include <QObject>
#endif

namespace Game
{

#ifdef GAME_OBJECTS_QT

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
