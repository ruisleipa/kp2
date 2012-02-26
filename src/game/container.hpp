#ifndef GAME_CONTAINER_HPP
#define GAME_CONTAINER_HPP

#ifdef KP2_CLIENT
#include <QObject>
#endif

#include <vector>
#include <algorithm>

#include "json/json.h" 
#include "objectfactory.hpp" 

namespace Game
{

#ifdef KP2_CLIENT

class ContainerSignals : public QObject
{
	Q_OBJECT
	
	signals:
		void childAdded(int index);
		void childRemoved(int index);
		void childChanged(int index);
};

#else

class ContainerSignals
{
	protected:
		void childAdded(int index){};
		void childRemoved(int index){};
		void childChanged(int index){};
};

#endif

template<class T>
class Container : public ContainerSignals
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
		
		int getIndexOf(T* item) const
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
		
		void add(T* item)
		{
			items.push_back(item);
		};

		void remove(T* item)
		{
			auto it = std::find(items.begin(), items.end(), item);

			if(it == items.end())
				return;

			items.erase(it);
		};
		
		virtual void save(Json::Value& value) const
		{
			for(T* item : items)
			{
				Json::Value i;
				
				item->save(i);
				
				value.append(i);
			}
		};
		
		Container(const Json::Value& value)
		{
			ObjectFactory factory;
		
			for(auto item : value)
			{
				Object* object = factory.create(item);
				
				T* item = dynamic_cast<T*>(object);
				
				if(item)
					items.push_back(new T(item));
			}
		};
		
		Container() = default;
	
	protected:
		Container(const Container& b)
		{
			*this = b;
		};
		
		Container& operator=(const Container& b)
		{
			for(T* item: b)
			{
				items.push_back(Object::clone(item));
			}
		};
	
	private:
		ContainerType items;
};

};

#endif
