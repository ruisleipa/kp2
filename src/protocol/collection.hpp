#ifndef PROTOCOL_COLLECTION_HPP
#define PROTOCOL_COLLECTION_HPP

#include <map>
#include <vector>
#include <stdint.h>

#include "net/packet.hpp"

namespace Protocol
{

template <typename Key, typename Type>
class Collection;

template <typename Key, typename Type>
Packet& operator<<(Packet& packet, const Collection<Key, Type>& collection)
{
	packet << uint32_t(collection.items.size());
	
	typename std::map<Key, Type>::const_iterator i;
	
	for(i = collection.items.begin(); i != collection.items.end(); ++i)
	{
		Key key = i->first;
		Type value = i->second;
		
		packet << key;
		packet << value;
	}
	
	return packet;
}

template <typename Key, typename Type>
Packet& operator>>(Packet& packet, Collection<Key, Type>& collection)
{
	collection.items.clear();

	uint32_t itemCount;
	
	packet >> itemCount;
	
	for(size_t i = 0; i < itemCount; ++i)
	{
		Key key;
		Type value;
		
		packet >> key;
		packet >> value;
		
		collection.items[key] = value;
	}
		
	return packet;
}

template <typename Key, typename Type>
class Collection
{
	public:
		std::vector<Key> getKeys() const;
		const Type& getItem(const Key& key) const;
		
		void addItem(const Key& key, const Type& item);
		
		friend Packet& operator<< <>(Packet& packet,const Collection& collection);
		friend Packet& operator>> <>(Packet& packet,Collection& collection);
		
	private:
		std::map<Key, Type> items;

};

template <typename Key, typename Type>
std::vector<Key> Collection<Key, Type>::getKeys() const
{
	std::vector<Key> keys;

	typename std::map<Key, Type>::const_iterator i;
	
	for(i = items.begin(); i != items.end(); ++i)
	{
		keys.push_back(i->first);
	}
	
	return keys;
}

template <typename Key, typename Type>
const Type& Collection<Key, Type>::getItem(const Key& key) const
{
	if(items.find(key) == items.end())
		throw 1;
		
	return items.find(key)->second;
}

template <typename Key, typename Type>
void Collection<Key, Type>::addItem(const Key& key, const Type& item)
{
	items[key] = item;
}

};

#endif
