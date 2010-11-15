#ifndef KEYEVENT_HPP
#define KEYEVENT_HPP

#include "areaevent.hpp"

#include <SDL/SDL.h>

class KeyEvent: public AreaEvent
{
	public:
		int getUnicode();
		SDLKey getKey();
				
		KeyEvent(const EventArea& area,int unicode,SDLKey key);
		
	private:
		int unicode;
		SDLKey key;
		
};

class KeyUpEvent: public KeyEvent
{
	public:
		KeyUpEvent(const EventArea& area,int unicode,SDLKey key):
			KeyEvent(area,unicode,key)
		{
		
		}
};

class KeyDownEvent: public KeyEvent
{
	public:
		KeyDownEvent(const EventArea& area,int unicode,SDLKey key):
			KeyEvent(area,unicode,key)
		{
		
		}
};

#endif // KEYEVENT_HPP
