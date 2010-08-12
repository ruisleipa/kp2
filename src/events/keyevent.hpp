#ifndef KEYEVENT_HPP
#define KEYEVENT_HPP

#include <graphics/window.hpp>
#include <SDL/SDL.h>
#include <stdint.h>

class KeyEvent
{
	public:
		uint16_t getUnicode();
		SDLKey getKey();
		Window& getWindow();
		
		KeyEvent(Window& window,uint16_t unicode,SDLKey key);
		
	private:
		Window& window;
		uint16_t unicode;
		SDLKey key;
		
};

#endif // KEYEVENT_HPP
