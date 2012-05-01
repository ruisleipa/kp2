#ifndef GAME_PARTCONTAINER_HPP
#define GAME_PARTCONTAINER_HPP

#include <map>
#include <list>

#include "exception.hpp"
#include "part.hpp"
#include "container.hpp"

namespace Game
{

class PartContainer : public Container<Part>
{
	public:
		class IncompatiblePartException : public Game::Exception
		{

		};

		class ExtraPartException : public Game::Exception
		{

		};

		typedef std::list<Part*> Parts;

		virtual void add(Part* part);
		virtual void remove(Part* part);

		Parts getAttachedParts(Part* part) const;
		Parts getAllAttachedParts(Part* part) const;

		PartContainer(const Json::Value& value, ObjectFactory& factory);
		virtual void save(Json::Value& value) const;

	private:
		void attachPart(Part* part, Part* partToAttach);

		std::map<Part*, Parts> attachments;
};

};

#endif
