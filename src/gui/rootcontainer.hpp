#ifndef ROOTCONTAINER_HPP
#define ROOTCONTAINER_HPP

#include "container.hpp"

#include "graphics/window.hpp"

#include "events/events.hpp"

class RootContainer : public Container
{
	public:
		virtual void onDraw(Window& window);
	
		RootContainer(Window& window,Events& events);
	
	private:
};

#endif // ROOTCONTAINER_HPP

