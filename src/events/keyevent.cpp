#include "keyevent.hpp"

uint16_t KeyEvent::getUnicode()
{
	return unicode;
}

SDLKey KeyEvent::getKey()
{
	return key;
}

Window& KeyEvent::getWindow()
{
	return window;
}

KeyEvent::KeyEvent(Window& window,uint16_t unicode,SDLKey key):
	window(window),
	unicode(unicode),
	key(key)
{

}
