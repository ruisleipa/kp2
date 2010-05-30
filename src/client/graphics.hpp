#ifndef __GRAPHICS_HPP
#define __GRAPHICS_HPP

#include <SDL/SDL.h>

#include "vector2d.hpp"
#include "texture.hpp"
#include <set>
#include <vector>

class Graphics
{
	public:
		static Graphics& getInstance();

		Vector2D getDisplaySize();

		void printVideoInfo();
				
		int setVideoMode(int width,int height,int bpp,bool fullscreen,bool vsync,bool doublebuffer);
		std::vector<Vector2D> getVideoModes();
		
		bool isVsynced();
		bool isFullscreen();
		
		void resize(Vector2D size);
		
		float getAspectRatio();
		
		void enterGuiMode();
		void exitGuiMode();

		~Graphics();

	private:

		void addTexture(Texture* texture);
		void removeTexture(Texture* texture);
		void refreshTextures();
		
		friend class Texture;
	
		Graphics();

		SDL_Surface* m_surface;
		
		std::set<Texture*> m_textures;

		int m_screen_width;
		int m_screen_height;
		int m_bpp;
		bool m_fullscreen;
		bool m_vsync;
		bool m_doublebuffer;
};

#endif // __GRAPHICS_HPP
