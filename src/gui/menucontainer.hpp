#ifndef MENUCONTAINER_HPP
#define MENUCONTAINER_HPP

#include "container.hpp"
#include "image.hpp"

#include "graphics/texturecollection.hpp"
#include "utils/timer.hpp"

class MenuContainer : public Container
{
	public:
		virtual void handleEvent(Event* event);
	
		virtual void showOnlyWidget(const std::string& tag);

		MenuContainer(TextureCollection& backgroundtextures);
	
	protected:
		void handleDrawEvent(DrawEvent* event);
	
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

