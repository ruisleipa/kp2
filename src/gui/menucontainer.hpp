#ifndef MENUCONTAINER_HPP
#define MENUCONTAINER_HPP

#include "container.hpp"
#include "image.hpp"

#include "utils/timer.hpp"
#include "graphics/texturecollection.hpp"

class MenuContainer: public Container
{
	public:
		void showMenu(std::string tag);
		void showOverlayMenu(std::string tag);
		virtual void onDraw(Window& window);
		
		void changeBackground();
		
		MenuContainer(TextureCollection& backgroundtextures);
	
	private:
		TextureCollection& backgroundtextures;
		Image backgroundFront;
		Image backgroundBack;
		Timer backgroundChangeTimer;

};

#endif // CONTAINER_HPP

