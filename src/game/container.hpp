#ifndef GAME_CONTAINER_HPP
#define GAME_CONTAINER_HPP

#include <vector>
#include <algorithm>

#include "json/json.h"
#include "object.hpp"
#include "objectfactory.hpp"

namespace Game
{

template<class T>
class Container : public Object::Listener
{
	public:
		typedef std::vector<T*> ContainerType;

		class Listener
		{
			public:
				virtual void onChange(Container<T>* container, int index) = 0;
				virtual void onAdd(Container<T>* container, int index) = 0;
				virtual void onRemove(Container<T>* container, int index) = 0;
		};

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

			item->addListener(this);
		};

		virtual void remove(T* item)
		{
			auto it = std::find(items.begin(), items.end(), item);

			if(it == items.end())
				return;

			int index = std::distance(items.begin(), it);

			item->removeListener(this);

			items.erase(it);

			removed(index);
		};

		virtual void save(Json::Value& value) const
		{
			value.resize(0);

			for(T* item : items)
			{
				Json::Value i;

				item->save(i);

				value.append(i);
			}
		};

		void addListener(Listener* listener) const
		{
			listeners.push_back(listener);
		};

		void removeListener(Listener* listener) const
		{
			listeners.erase(std::find(listeners.begin(), listeners.end(), listener));
		};

		Container(const Json::Value& value, ObjectFactory& factory)
		{
			for(auto item : value)
			{
				Object* object = factory.create(item);

				T* ptr = dynamic_cast<T*>(object);

				if(ptr)
					add(ptr);
				else
					std::cerr << "Invalid item in container" << std::endl << item << std::endl;
			}
		};

		virtual void onChange(Object* object)
		{
			// This cast is safe because the objects connected
			// by the add-method are always of the correct type.
			T* item = static_cast<T*>(object);

			auto it = std::find(items.begin(), items.end(), item);

			if(it == items.end())
				return;

			int index = std::distance(items.begin(), it);

			changed(index);
		};

		Container() = default;

	protected:
		Container(const Container& b)
		{
			*this = b;
		};

	private:
		void added(int index)
		{
			for(Listener* listener : listeners)
				listener->onAdd(this, index);
		}

		void removed(int index)
		{
			for(Listener* listener : listeners)
				listener->onRemove(this, index);
		}

		void changed(int index)
		{
			for(Listener* listener : listeners)
				listener->onChange(this, index);
		}

		ContainerType items;

		mutable std::vector<Listener*> listeners;
};

};

#endif
