#ifndef ROOTCONTAINER_HPP
#define ROOTCONTAINER_HPP

#include "widgetcontainer.hpp"

#include "graphics/window.hpp"

#include "events/events.hpp"

class RootContainer : public WidgetContainer
{
	public:
		RootContainer(Window& window,Events& events);
	
	private:
};

#endif // ROOTCONTAINER_HPP

