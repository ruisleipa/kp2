#ifndef GAME_PARTCONTAINER_HPP
#define GAME_PARTCONTAINER_HPP

#include <string>
#include <map>
#include <memory>

#include "object.hpp"

namespace Game
{

class Part;

class PartContainer : public Object
{
	public:
		class Slot
		{
			public:
				class AlreadyInUseException
				{

				};

				class IncompatibleTypeException
				{

				};

				virtual Part* getPart() const;
				virtual Part* detachPart();
				virtual void attachPart(Part* part);

			private:
				std::unique_ptr<Part> part;
		};

		typedef const std::map<std::string, Slot*>& Slots;

		Slots getSlots() const;
		Slot& getSlotByName(const std::string& name) const;

		PartContainer() = default;
		PartContainer(const Json::Value&);

	protected:
		template <class T>
		class TypedSlot : public Slot
		{
			public:
				virtual T* getPart() const
				{
					return static_cast<T*>(Slot::getPart());
				}

				virtual T* detachPart()
				{
					return static_cast<T*>(Slot::detachPart());
				}

				virtual void attachPart(Part* part)
				{
					if(dynamic_cast<T*>(part))
						Slot::attachPart(part);
					else
						throw Slot::IncompatibleTypeException();
				}

				TypedSlot() = default;

				TypedSlot(const Json::Value& value)
				{
					if(!value.isNull())
					{
						T* part = new T(value);

						attachPart(part);
					}
				}

				virtual void save(Json::Value& value) const
				{
					if(getPart())
					{
						Json::Value part;

						getPart()->save(part);

						value = part;
					}
					else
					{
						value = Json::Value();
					}
				}
		};

		void registerSlot(const std::string& name, Slot* slot);

	private:
		std::map<std::string, Slot*> registeredSlots;
};

};

#endif
