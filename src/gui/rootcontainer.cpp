#include "rootcontainer.hpp"

void RootContainer::onDraw(Window& window)
{
	setPixelSize(window.getSize());
}

RootContainer::RootContainer(Window& window,Events& events)
{
	events.setEventListener(this);
}
