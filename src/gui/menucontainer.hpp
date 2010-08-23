#ifndef MENUCONTAINER_HPP
#define MENUCONTAINER_HPP

#include "container.hpp"
#include "image.hpp"
#include "utils/timer.hpp"

class MenuContainer: public Container
{
	public:
		void showMenu(std::string tag);
		void showOverlayMenu(std::string tag);
		virtual void onDraw(Graphics& graphics);
		
		void changeBackground();
		
		MenuContainer(TextureCollection& backgroundtextures);
	
	private:
		Image background;
		Timer backgroundChangeTimer;

};

#endif // CONTAINER_HPP

