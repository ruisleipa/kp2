#include "keyevent.hpp"

int KeyEvent::getUnicode()
{
	return unicode;
}

SDLKey KeyEvent::getKey()
{
	return key;
}

KeyEvent::KeyEvent(const EventArea& area,int unicode,SDLKey key):
	Event(area),
	unicode(unicode),
	key(key)
{

}
