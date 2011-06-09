#include "rootcontainer.hpp"

void RootContainer::onDraw(Window& window)
{

}

RootContainer::RootContainer(Window& window,Events& events)
{
	events.setEventListener(this);
}
