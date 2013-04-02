#ifndef GAME_OBJECT_HPP
#define GAME_OBJECT_HPP

#include "serializable.hpp"

namespace Game
{

class Object : public Serializable
{
	public:
		class Listener
		{
			public:
				virtual void onChange(Object* object) = 0;
		};

		void addListener(Listener* listener);
		void removeListener(Listener* listener);

		void save(Json::Value &) const;

		Object() = default;
		Object(const Json::Value&);

	protected:
		Object(const Object&) = default;
		Object& operator=(const Object&);

		void changed();

	private:
		std::vector<Listener*> listeners;
};




};

#endif
