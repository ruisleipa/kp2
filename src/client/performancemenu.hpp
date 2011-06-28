#ifndef CLIENT_PERFORMANCEMENU_HPP
#define CLIENT_PERFORMANCEMENU_HPP

#include "gui/menu.hpp"
#include "gui/widgetloader.hpp"

class Connection;

class PerformanceMenu : public Menu
{
	public:
		PerformanceMenu(Connection& connection, Container& parent);

	private:
		void handleConnectionEvent();
		
		void fillPerformanceGraph();
		void fillBoostGraph();
		void fillAirGraph();
		void fillFuelGraph();
		void fillTemperatureGraph();
		
		void showGraph(const std::string& name);
	
		Connection& connection;
		
		WidgetLoader loader;
};

#endif // INSTALLPARTSMENU_HPP
