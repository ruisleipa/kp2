#ifndef MENUCONTAINER_HPP
#define MENUCONTAINER_HPP

#include "container.hpp"
#include "image.hpp"

#include "graphics/texturecollection.hpp"
#include "utils/timer.hpp"

class MenuContainer : public Container
{
	public:
		virtual void showOnlyWidget(const std::string& tag);

		virtual void onDraw(Window& window);
		
		MenuContainer(TextureCollection& backgroundtextures);
	
	private:
		void changeBackground();
		int getRandomTextureIndex();
	
		TextureCollection& backgroundtextures;
		int backgroundIndex;
		
		Image backgroundFront;
		Image backgroundBack;
		Timer backgroundChangeTimer;
};

#endif // MENUCONTAINER_HPP

