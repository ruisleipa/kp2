#ifndef MENUCONTAINER_HPP
#define MENUCONTAINER_HPP

#include "container.hpp"
#include "image.hpp"

#include "utils/timer.hpp"
#include "graphics/texturecollection.hpp"

#include <map>

class Menu;

class MenuContainer: public Container
{
	public:
		void showMenu(std::string menu);
		void showOverlayMenu(std::string menu);
		void addMenu(std::string name,Menu& menu);
		
		virtual void onDraw(Window& window);
		
		void changeBackground();
		
		MenuContainer(TextureCollection& backgroundtextures);
	
	private:
		int getRandomTextureIndex();
	
		TextureCollection& backgroundtextures;
		int backgroundIndex;
		
		Image backgroundFront;
		Image backgroundBack;
		Timer backgroundChangeTimer;
		
		std::map<std::string,Menu*> menus;

};

#endif // CONTAINER_HPP

