#include "playervehiclebutton.hpp"

#include <sstream>

#include "graphics/texture.hpp"
#include "connection.hpp"
#include "gui/container.hpp"
#include "gui/label.hpp"
#include "gui/image.hpp"

void PlayerVehicleButton::showVehicle(Connection& connection, size_t vehicleId)
{
	const Protocol::Vehicle& vehicle = connection.getPlayerVehicles().getItem(vehicleId);
	
	Container& container = dynamic_cast<Container&>(loader.getRootWidget());
	
	Image& image = container.getChildByName<Image>("image");
	
	std::string file = "gamedata/vehicleimages/" + vehicle.imageName;
	image.setTexture(Texture(file));
	
	std::stringstream ss;
	
	ss << vehicle.name << " vm. " << vehicle.year << "\n";
	ss << "Tekniikka: jotain tekniikasta" << "\n";
	ss << "Paino: " << vehicle.totalWeight << " kg\n";
	ss << "Jotain: jotain" << "\n";
	
	Label& info = container.getChildByName<Label>("info");
	
	info.setText(ss.str());
	
	bool selected = false;
	
	if(vehicleId == connection.getActiveVehicleId())
		selected = true;
		
	container.getChildByName("selectedSkin").setVisible(selected);
	container.getChildByName("normalSkin").setVisible(!selected);
}

void PlayerVehicleButton::handleEvent(Event* event)
{
	if(dynamic_cast<DrawEvent*>(event))
		handleDrawEvent(dynamic_cast<DrawEvent*>(event));
	else
		Button::handleEvent(event);
}

PlayerVehicleButton::PlayerVehicleButton():
	loader("data/widgets/playervehiclebutton.ui")
{

}

void PlayerVehicleButton::handleDrawEvent(DrawEvent* event)
{
	loader.getRootWidget().handleEvent(event);
}
