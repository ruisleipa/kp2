#include "loadingscreen.hpp"

#include "utils/sdl.hpp"
#include "graphics/texture.hpp"
#include "graphics/color.hpp"
#include "graphics/window.hpp"

#include "gui/container.hpp"
#include "gui/freecontainer.hpp"
#include "gui/widget.hpp"

#include <GL/gl.h>

void LoadingScreen::setTotalLoadCount(int totalLoads)
{
	this->totalLoads = totalLoads;
}
	
void LoadingScreen::progress()
{
	loads++;
	
	Container& root = dynamic_cast<Container&>(loader.getRootWidget());
	Widget& bar = root.getChildByName("bar");
	FreeContainer& container = root.getChildByName<FreeContainer>("barContainer");
	
	std::stringstream width;
	
	width << float(loads) / float(totalLoads) * 100.0 << "%";
	
	container.setWidgetSize(bar, width.str(), "100%");
	
	draw();
}

LoadingScreen::LoadingScreen(Window& window):
	window(window),
	loader("data/ui/loadingscreen.ui"),
	totalLoads(0),
	loads(0)
{

}

void LoadingScreen::draw()
{
	glClearColor(0, 0, 0, 0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	EventArea eventArea(window, Vector2D(0,0), window.getSize());
	DrawEvent drawEvent(eventArea);
	
	loader.getRootWidget().handleEvent(&drawEvent);
	
	SDL_GL_SwapBuffers();
}
