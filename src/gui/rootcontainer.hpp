#ifndef GUI_ROOTCONTAINER_HPP
#define GUI_ROOTCONTAINER_HPP

#include "freecontainer.hpp"

#include "graphics/window.hpp"

#include "events/events.hpp"

class RootContainer : public FreeContainer
{
	public:
		virtual void onDraw(Window& window);
	
		RootContainer(Window& window,Events& events);
	
	private:
};

#endif

