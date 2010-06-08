#ifndef __GRAPHICS_HPP
#define __GRAPHICS_HPP

class Events;
#include "sdl.hpp"
#include "vector2d.hpp"
#include <vector>

class Graphics
{
	public:
		Vector2D getDisplaySize();

		void printVideoInfo();
				
		int setVideoMode(int width,int height,int bpp,bool fullscreen,bool vsync,bool doublebuffer);
		std::vector<Vector2D> getVideoModes();
		
		bool isDoubleBuffered();
		bool isVsynced();
		bool isFullScreen();
		int getBitsPerPixel();
		
		void resize(Vector2D size);
		
		float getAspectRatio();
		
		void enterGuiMode();
		void exitGuiMode();
		
		Graphics(Sdl& sdl,Events& events);
		~Graphics();

	private:
		Sdl& m_sdl;
		Events& m_events;
		SDL_Surface* m_surface;		
};

#endif // __GRAPHICS_HPP
