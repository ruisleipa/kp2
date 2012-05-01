#ifndef GAME_CONTAINER_HPP
#define GAME_CONTAINER_HPP

#include <vector>
#include <algorithm>

#include "json/json.h"
#include "objectfactory.hpp"
#include "containersignalsandslots.hpp"

namespace Game
{

template<class T>
class Container : public ContainerSignalsAndSlots
{
	public:
		typedef std::vector<T*> ContainerType;

		typename ContainerType::iterator begin()
		{
			return items.begin();
		};

		typename ContainerType::const_iterator begin() const
		{
			return items.begin();
		};

		typename ContainerType::iterator end()
		{
			return items.end();
		};

		typename ContainerType::const_iterator end() const
		{
			return items.end();
		};

		int getIndexOf(const T* item) const
		{
			auto it = std::find(items.begin(), items.end(), item);

			if(it == items.end())
				return -1;

			return std::distance(items.begin(), it);
		};

		T* getByIndex(int index) const
		{
			if(index < 0)
				return nullptr;

			auto it = items.begin();

			std::advance(it, index);

			if(it == items.end())
				return nullptr;

			return *it;
		};

		bool contains(const T* item) const
		{
			auto it = std::find(items.begin(), items.end(), item);

			if(it == items.end())
				return false;

			return true;
		};

		int getItemCount() const
		{
			return items.size();
		}

		virtual void add(T* item)
		{
			items.push_back(item);

			added(items.size() - 1);

#ifdef KP2_CLIENT
			connect(item, SIGNAL(changed()), this, SLOT(onChange()));
#endif
		};

		virtual void remove(T* item)
		{
			auto it = std::find(items.begin(), items.end(), item);

			if(it == items.end())
				return;

			int index = std::distance(items.begin(), it);

#ifdef KP2_CLIENT
			item->disconnect(SIGNAL(changed()), this, SLOT(onChange()));
#endif

			items.erase(it);

			removed(index);
		};

		virtual void save(Json::Value& value) const
		{
			value["items"].resize(0);

			for(T* item : items)
			{
				Json::Value i;

				item->save(i);

				value["items"].append(i);
			}
		};

		Container(const Json::Value& value, ObjectFactory& factory)
		{
			for(auto item : value["items"])
			{
				Object* object = factory.create(item);

				T* ptr = dynamic_cast<T*>(object);

				if(ptr)
					items.push_back(ptr);
				else
					std::cerr << "Invalid item in container" << std::endl << item << std::endl;
			}
		};

		Container() = default;

	protected:
		Container(const Container& b)
		{
			*this = b;
		};

#ifdef KP2_CLIENT
		virtual void onChange()
		{
			// This cast is safe because the objects connected
			// to this slot by the add-method are always of the
			// correct type.
			T* item = static_cast<T*>(sender());

			auto it = std::find(items.begin(), items.end(), item);

			if(it == items.end())
				return;

			int index = std::distance(items.begin(), it);

			changed(index);
		};
#endif

	private:
		ContainerType items;
};

};

#endif
