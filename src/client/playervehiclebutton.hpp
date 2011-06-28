#ifndef CLIENT_PLAYERVEHICLEBUTTON_HPP
#define CLIENT_PLAYERVEHICLEBUTTON_HPP

#include "gui/button.hpp"
#include "gui/widgetloader.hpp"

class Connection;

class PlayerVehicleButton : public Button
{
	public:
		void showVehicle(Connection& connection, size_t vehicleId);
		
		void handleEvent(Event* event);
		
		PlayerVehicleButton();
		
	private:
		void handleDrawEvent(DrawEvent* event);
	
		WidgetLoader loader;
		
};

#endif
