#ifndef GAME_OBJECT_HPP
#define GAME_OBJECT_HPP

#include <vector>

#ifdef KP2_CLIENT
#include <QObject>
#else
#define Q_OBJECT
#define signals public
class QObject{};

#endif

#include "json/json.h" 

namespace Game
{

class Object : public QObject
{
	Q_OBJECT

	public:
		typedef std::vector<Object*> Container;
		
		Container::iterator begin();
		Container::const_iterator begin() const;
		Container::iterator end();
		Container::const_iterator end() const;		
		
		template<class Type>
		std::vector<Type*> getChildren() const
		{
			std::vector<Type*> children;
		
			for(Object* obj : *this)
			{
				Type* typed = dynamic_cast<Type*>(obj);
				
				if(typed)
					children.push_back(typed);
			}
			
			return children;
		}
	
		const std::string& getName() const;
		void setName(const std::string&);
	
		Object* findChild(const std::string& name);
		Object* getChild(int index);
		
		Json::Value getId(Object*);
		Object* resolveId(const Json::Value& path);
		
		bool addChild(Object* v);
		void removeChild(Object*);
		
		virtual Object* clone() const;
		
		virtual void save(Json::Value&);
		
		Object(const Json::Value&);
		Object();
	
	signals:
		void childAdded(int index);
		void childRemoved(int index);
		void childChanged(int index);
		void changed();
	
	protected:
		Object(const Object&);
		Object& operator=(const Object&);
	
		virtual bool canAddChild(Object*);
	
	private:
		int getChildIndex(Object*);
		bool isObjectInTree(Object*);
		void setParent(Object*);
				
		Object* parent;
		
		Container children;
		
		std::string name;
		
};

};

#endif
