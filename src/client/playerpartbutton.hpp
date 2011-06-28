#ifndef CLIENT_PLAYERPARTBUTTON_HPP
#define CLIENT_PLAYERPARTBUTTON_HPP

#include "gui/button.hpp"
#include "gui/widgetloader.hpp"

#include "protocol/part.hpp"

class PlayerPartButton : public Button
{
	public:
		void showPart(Protocol::Part& part);
		
		void handleEvent(Event* event);
		
		Vector2D getAutoSize();
		
		PlayerPartButton();
		
	private:
		void handleDrawEvent(DrawEvent* event);
	
		WidgetLoader loader;
		
};

#endif
