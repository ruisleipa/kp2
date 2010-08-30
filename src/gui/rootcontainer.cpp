#include "rootcontainer.hpp"

RootContainer::RootContainer(Window& window,Events& events)
{
	events.setEventListener(this);
}
