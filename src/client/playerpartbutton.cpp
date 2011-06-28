#include "playerpartbutton.hpp"

#include <sstream>

#include "graphics/texture.hpp"
#include "gui/container.hpp"
#include "gui/label.hpp"

void PlayerPartButton::showPart(Protocol::Part& part)
{
	Container& container = dynamic_cast<Container&>(loader.getRootWidget());
	
	Container& imageContainer = container.getChildByName<Container>("imageContainer");
	imageContainer.showOnlyWidget(part.type);
	
	container.getChildByName<Label>("name").setText(part.name);
}

void PlayerPartButton::handleEvent(Event* event)
{
	if(dynamic_cast<DrawEvent*>(event))
		handleDrawEvent(dynamic_cast<DrawEvent*>(event));
	else
		Button::handleEvent(event);
}

Vector2D PlayerPartButton::getAutoSize()
{
	return loader.getRootWidget().getAutoSize();
}

PlayerPartButton::PlayerPartButton():
	loader("data/widgets/playerpartbutton.ui")
{

}

void PlayerPartButton::handleDrawEvent(DrawEvent* event)
{
	loader.getRootWidget().handleEvent(event);
}
