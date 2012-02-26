#ifndef GAME_CONTAINER_HPP
#define GAME_CONTAINER_HPP

#ifdef KP2_CLIENT
#include <QObject>
#endif

#include <vector>

#include "json/json.h" 

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
	
		typename ContainerType::iterator begin();
		typename ContainerType::const_iterator begin() const;
		typename ContainerType::iterator end();
		typename ContainerType::const_iterator end() const;
		
		int getIndexOf(T*) const;
		T* getByIndex(int index) const;
		
		bool add(T*);
		void remove(T*);
		
		virtual Container* clone() const;
		
		virtual void save(Json::Value&) const;
		
		Container(const Json::Value&);
		Container();
	
	protected:
		Container(const Container&);
		Container& operator=(const Container&);
	
	private:
		ContainerType children;
};

};

#endif
