#ifndef MENU_HPP
#define MENU_HPP

#include <string>

#include "freecontainer.hpp"
#include "gui/widgetloader.hpp"

class Menu : public FreeContainer
{
	public:
		void handleEvent(Event* event);
	
		Menu(std::string uifile);
		Menu();
	
	protected:
		virtual void connectFunctionality();
	
	private:
		std::string uifile;
		std::tr1::shared_ptr<WidgetLoader> loader;
};

#endif // MENU_HPP

