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
		
		virtual void onDraw(Window& window);
		
	protected:
		void changeBackground();
		
		void addMenu(std::string name,Menu& menu);
		
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

#endif // MENUCONTAINER_HPP

