#include "loadingscreen.hpp"

#include "utils/sdl.hpp"
#include "graphics/texture.hpp"
#include "graphics/color.hpp"
#include "graphics/window.hpp"

#include <GL/gl.h>

void LoadingScreen::setTotalLoadCount(int totalLoads)
{
	this->totalLoads = totalLoads;
}
	
void LoadingScreen::progress()
{
	loads++;
	
	draw();
}

LoadingScreen::LoadingScreen(Window& window):
	window(window),
	totalLoads(0),
	loads(0)
{

}

void LoadingScreen::draw()
{
	glClearColor(0,0,0,0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	Texture().bind();
	
	drawBar();
	drawFrame();
	
	SDL_GL_SwapBuffers();
}

void LoadingScreen::drawFrame()
{
	Color(1,1,1).apply();

	Vector2D size = window.getSize();
	
	glBegin(GL_LINE_LOOP);	
		glVertex2d(size.getX() * 0.2, size.getY() * 0.45);
		glVertex2d(size.getX() * (0.2 + 0.6), size.getY() * 0.45);	
		glVertex2d(size.getX() * (0.2 + 0.6), size.getY() * 0.55);			
		glVertex2d(size.getX() * 0.2, size.getY() * 0.55);	
	glEnd();
}

void LoadingScreen::drawBar()
{
	Color(1,1,1).apply();

	Vector2D size = window.getSize();
	
	glBegin(GL_QUADS);	
		glVertex2d(size.getX() * 0.2, size.getY() * 0.45);
		glVertex2d(size.getX() * (0.2 + 0.6 * (float(loads) / float(totalLoads))), size.getY() * 0.45);	
		glVertex2d(size.getX() * (0.2 + 0.6 * (float(loads) / float(totalLoads))), size.getY() * 0.55);			
		glVertex2d(size.getX() * 0.2, size.getY() * 0.55);	
	glEnd();
}
