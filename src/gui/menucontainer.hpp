#ifndef GUI_MENUCONTAINER_HPP
#define GUI_MENUCONTAINER_HPP

#include "freecontainer.hpp"
#include "image.hpp"

#include "graphics/texturecollection.hpp"
#include "utils/timer.hpp"

class MenuContainer : public FreeContainer
{
	public:
		void addWidget(const std::string& name, Widget& widget);
		
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

#endif

