#ifndef KEYEVENT_HPP
#define KEYEVENT_HPP

#include "event.hpp"

#include <SDL/SDL.h>

class KeyEvent: public Event
{
	public:
		int getUnicode();
		SDLKey getKey();
				
		KeyEvent(const EventArea& area,int unicode,SDLKey key);
		
	private:
		int unicode;
		SDLKey key;
		
};

#endif // KEYEVENT_HPP
