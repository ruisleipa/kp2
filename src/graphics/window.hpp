#ifndef WINDOW_HPP
#define WINDOW_HPP

#include "utils/sdl.hpp"
#include "utils/inifile.hpp"

#include "vector2d.hpp"

#include <vector>

class Window
{
	public:
		Vector2D getSize();
		std::vector<Vector2D> getPossibleSizes();
		
		float getAspectRatio();
		
		void setVideoMode(Vector2D size,int bpp,bool fullscreen);
		
		void setVsyncPreference(bool vsync);
		bool getVsyncPreference();
		
		bool isFullscreen();
		
		int getBitsPerPixel();
		
		bool hasModeChanged();
		void clearModeChangeFlag();
		
		Window(Sdl& sdl);
		~Window();

	private:
		Vector2D surfaceSize;
		int surfaceBpp;
		bool surfaceFullscreen;
		bool vsyncPreference;
		
		float aspectRatio;
		
		SDL_Surface* surface;

		bool modeChanged;
		
		IniFile settings;
			
		void loadSettings();
		void saveSettings();

		void createSurface();
		void setAttributes();
		void checkAttributes();
		
		void calculateAspectRatio();
		void initOpenGL();
		void initGLEW();
		
		void applyDefaultSettings();

};

#endif // WINDOW_HPP
