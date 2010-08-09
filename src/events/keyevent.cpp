#include "keyevent.hpp"

uint16_t KeyEvent::getUnicode()
{
	return m_unicode;
}

SDLKey KeyEvent::getKey()
{
	return m_key;
}

KeyEvent::KeyEvent(uint16_t unicode,SDLKey key)
{
	m_unicode=unicode;
	m_key=key;
}
