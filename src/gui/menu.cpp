#include "menu.hpp"

void Menu::handleEvent(Event* event)
{
	FreeContainer::handleEvent(event);
}

Menu::Menu(std::string uifile):
	uifile(uifile),
	loader(std::tr1::shared_ptr<WidgetLoader>(new WidgetLoader(uifile)))
{
	addWidget(loader->getRootWidget(), "0px", "0px", "100%", "100%");
	
	connectFunctionality();
}

Menu::Menu()
{
	
}

void Menu::connectFunctionality()
{

}
