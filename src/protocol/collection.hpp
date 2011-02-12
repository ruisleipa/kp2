#ifndef PROTOCOL_COLLECTION_HPP
#define PROTOCOL_COLLECTION_HPP

#include <vector>
#include <stdint.h>

#include "net/packet.hpp"

namespace Protocol
{

template <typename T>
class Collection;

template <typename T>
Packet& operator<<(Packet& packet,const Collection<T>& collection)
{
	packet << uint32_t(collection.items.size());
	
	for(size_t i = 0; i < collection.items.size(); ++i)
	{
		packet << collection.items[i];
	}
	
	return packet;
}

template <typename T>
Packet& operator>>(Packet& packet,Collection<T>& collection)
{
	collection.items.clear();

	uint32_t itemCount;
	
	packet >> itemCount;
	
	for(size_t i = 0; i < itemCount; ++i)
	{
		T item;
		
		packet >> item;
		
		collection.items.push_back(item);
	}
		
	return packet;
}

template <typename T>
class Collection
{
	public:
		size_t getItemCount() const;
		T getItem(size_t index) const;
		void addItem(const T& item);
		
		friend Packet& operator<< <>(Packet& packet,const Collection& collection);
		friend Packet& operator>> <>(Packet& packet,Collection& collection);
		
	private:
		std::vector<T> items;

};

template <typename T>
size_t Collection<T>::getItemCount() const
{
	return items.size();
}

template <typename T>
T Collection<T>::getItem(size_t index) const
{
	return items.at(index);
}

template <typename T>
void Collection<T>::addItem(const T& item)
{
	items.push_back(item);
}



};

#endif
