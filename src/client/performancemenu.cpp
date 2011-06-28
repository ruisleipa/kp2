#include "performancemenu.hpp"

#include "connection.hpp"

#include "gui/button.hpp"
#include "gui/graph.hpp"

#include <windows.h>

PerformanceMenu::PerformanceMenu(Connection& connection, Container& parent):
	connection(connection),
	loader("data/ui/performancemenu.ui")
{
	addWidget(loader.getRootWidget(), "0px", "0px", "100%", "100%");
	
	connection.addEventHandler(std::tr1::bind(&PerformanceMenu::handleConnectionEvent,this));
	
	getChildByName<Button>("performaceButton").setClickHandler(std::tr1::bind(&PerformanceMenu::showGraph, this, "performanceGraph"));
	getChildByName<Button>("boostCurveButton").setClickHandler(std::tr1::bind(&PerformanceMenu::showGraph, this, "boostGraph"));
	getChildByName<Button>("flowCurveButton").setClickHandler(std::tr1::bind(&PerformanceMenu::showGraph, this, "flowGraph"));
	getChildByName<Button>("fuelButton").setClickHandler(std::tr1::bind(&PerformanceMenu::showGraph, this, "fuelGraph"));
	getChildByName<Button>("temperatureButton").setClickHandler(std::tr1::bind(&PerformanceMenu::showGraph, this, "temperatureGraph"));
	getChildByName<Button>("backButton").setClickHandler(std::tr1::bind(&Container::showOnlyWidget, &parent, "installpartsmenu"));
}

void PerformanceMenu::handleConnectionEvent()
{
	fillPerformanceGraph();
	fillPerformanceGraph();
	fillBoostGraph();
	fillAirGraph();
	fillFuelGraph();
	fillTemperatureGraph();
}

void PerformanceMenu::fillPerformanceGraph()
{
	Graph& graph = dynamic_cast<Graph&>(getChildByName("performanceGraph"));

	const Protocol::PerformanceData data = connection.getPerformanceData();
		
	graph.setPrimaryData(data.power, Color(1, 0, 0), "Teho\n(kW)", data.power.getMax() * 1.25);
	graph.setSecondaryData(data.torque, Color(0, 0, 1), "Vääntö\n(Nm)", data.torque.getMax() * 2.5);
	graph.setDomain(0, 10000);
}

void PerformanceMenu::fillBoostGraph()
{
	Graph& graph = dynamic_cast<Graph&>(getChildByName("boostGraph"));

	const Protocol::PerformanceData data = connection.getPerformanceData();
		
	graph.setPrimaryData(data.boost, Color(1, 0, 0), "Ahtopaine", data.boost.getMax());
	graph.setDomain(0, 10000);
}

void PerformanceMenu::fillAirGraph()
{
	Graph& graph = dynamic_cast<Graph&>(getChildByName("flowGraph"));

	const Protocol::PerformanceData data = connection.getPerformanceData();
		
	float range = std::max(data.intake.getMax(), data.exhaust.getMax()) * 1.25;
	
	graph.setPrimaryData(data.intake, Color(0, 0, 1), "Imu\n(L / min)", range);
	graph.setSecondaryData(data.exhaust, Color(1, 0, 0), "Pako\n(L / min)", range);
	graph.setDomain(0, 10000);
}

void PerformanceMenu::fillFuelGraph()
{
	Graph& graph = dynamic_cast<Graph&>(getChildByName("fuelGraph"));

	const Protocol::PerformanceData data = connection.getPerformanceData();
		
	graph.setDomain(0, 10000);
}

void PerformanceMenu::fillTemperatureGraph()
{
	Graph& graph = dynamic_cast<Graph&>(getChildByName("temperatureGraph"));

	const Protocol::PerformanceData data = connection.getPerformanceData();
		
	graph.setPrimaryData(data.intakeTemperature, Color(1, 0, 0), "Imuilma\n(°C)", data.intakeTemperature.getMax());
	graph.setDomain(0, 10000);
}

void PerformanceMenu::showGraph(const std::string& name)
{
	Container& container = dynamic_cast<Container&>(getChildByName("graphContainer"));
	container.showOnlyWidget(name);
}

