#include <iostream>

#include "vehicle.hpp"
#include "engine.hpp"
#include "graph.hpp"
#include "curve.hpp"
#include "pipe.hpp"
#include "math_tools.hpp"

#include "sounds/sound.hpp"
#include "utils/sdl.hpp"
#include "utils/timer.hpp"
#include "graphics/color.hpp"
#include "graphics/window.hpp"
#include "graphics/fontface.hpp"
#include "events/events.hpp"

class DataPoint
{
	public:
		float speed;
		float torque;
		float power;
		float maxIntake;
		float maxExhaust;
		float freshMixture;
		float usedMixture;
		
		DataPoint():
			speed(0),
			torque(0),
			power(0),
			maxIntake(0),
			maxExhaust(0),
			freshMixture(0),
			usedMixture(0)
		{
		
		}
};

float round(float a, float s)
{
	float b = 0.0;
	
	while(b < a)
		b += s;
	
	return b;
}

int main(int argc, char** argv)
{
	Curve torqueCurve;
	
	torqueCurve.addPoint(0, 0);
	torqueCurve.addPoint(1500, 65);
	torqueCurve.addPoint(2000, 75);
	torqueCurve.addPoint(2500, 78);
	torqueCurve.addPoint(3000, 78);
	torqueCurve.addPoint(4000, 73);
	torqueCurve.addPoint(4900, 65);
	torqueCurve.addPoint(6000, 50);
	torqueCurve.addPoint(8000, 0);
	torqueCurve.addPoint(100000, 0);
	
	float idleSpeed = 1000.0;
	float speedLimit = 6500.0;
	
	Pipe intakePipe(8000);
	Pipe exhaustPipe(10000);
	
	Engine engine(torqueCurve, 1.0, 4, intakePipe, exhaustPipe, idleSpeed, 0.3, speedLimit, 2000, 0.22);
		
	std::vector<float> gearRatios;
	gearRatios.push_back(-2.86);
	gearRatios.push_back(0);
	gearRatios.push_back(3.9);
	gearRatios.push_back(2.6);
	gearRatios.push_back(1.9);
	gearRatios.push_back(1.0);
	gearRatios.push_back(0.7);
	
	Transmission transmission(gearRatios, 1, 0.8, 4.22, 0.1);
	Clutch clutch(600);
	
	Chassis chassis;
	
	chassis.totalMass = 1000.0;
	chassis.massOnRear = 500;
	chassis.centerOfGravityHeight = 0.3;
	chassis.length = 2.8;
	chassis.width = 1.7;
	chassis.wheelBase = 2.0;
	chassis.dragCoefficient = 0.4;
	
	Tire frontLeftTire(9, 0.3048, 0.015);
	Tire frontRightTire(9, 0.3048, 0.015);
	Tire backLeftTire(9, 0.3048, 0.015);
	Tire backRightTire(9, 0.3048, 0.015);
	Brake brake(0.8, 6000);
	
	Vehicle vehicle(engine, transmission, clutch, chassis, frontLeftTire, frontRightTire, backLeftTire, backRightTire, brake, brake, brake, brake);

	Sdl sdl;
	Window window(sdl);
	Events events(window);

	FontFace debugFont(window, "data/fonts/dejavusans.ttf", 12);
	
	int nextSpeed = 0;
	const int speedStep = 250;
	
	std::vector<DataPoint> data;
	
	Timer realTime;
	
	while(/*vehicle.getEngineSpeed() < speedLimit && */vehicle.getLagInSteps(60.0) > 0)
	{
		vehicle.advanceSimulation();
			
		if(vehicle.getEngineSpeed() < idleSpeed)
			engine.setIgnition(true);
		else
			engine.setIgnition(false);
			
		if(vehicle.getEngineSpeed() >= idleSpeed)
			engine.setThrottle(1.0);
			
		if(vehicle.getEngineSpeed() >= nextSpeed && vehicle.getEngineSpeed() > 1000)		
		{
			DataPoint dataPoint;
			
			dataPoint.speed = vehicle.getEngineSpeed();
			dataPoint.torque = engine.getTorque(vehicle.getEngineSpeed() * RPM_TO_RADS);
			dataPoint.power = dataPoint.torque * (vehicle.getEngineSpeed() * RPM_TO_RADS) / 1000.0;
			dataPoint.maxIntake = engine.calculateMaxFromIntakeManifold(vehicle.getEngineSpeed());
			dataPoint.maxExhaust = engine.calculateMaxToExhaustManifold(vehicle.getEngineSpeed());
			dataPoint.freshMixture = engine.calculateFreshMixtureInCylinder(vehicle.getEngineSpeed());
			dataPoint.usedMixture = engine.calculateExhaustLeftInCylinder(vehicle.getEngineSpeed());
			
			data.push_back(dataPoint);
			
			nextSpeed += speedStep;
		}
	}
	
	std::cout << "Calculation took " << realTime.getSeconds() << " seconds." << std::endl; 
	
	Curve torqueData;
	Curve powerData;
	Curve maxIntakeData;
	Curve maxExhaustData;
	Curve freshMixtureData;
	Curve usedMixtureData;
	
	for(std::vector<DataPoint>::size_type i = 0; i < data.size(); ++i)
	{
		DataPoint& dataPoint = data[i];
		int speed = dataPoint.speed;

		powerData.addPoint(speed, dataPoint.power);
		torqueData.addPoint(speed, dataPoint.torque);
		maxIntakeData.addPoint(speed, dataPoint.maxIntake);
		maxExhaustData.addPoint(speed, dataPoint.maxExhaust);
		freshMixtureData.addPoint(speed, dataPoint.freshMixture);
		usedMixtureData.addPoint(speed, dataPoint.usedMixture);
	}

	FontFace graphFont(window, "data/fonts/dejavusans.ttf", 8);
	
	Graph performanceGraph(graphFont);
	performanceGraph.setPrimaryData(powerData, Color(1, 0, 0), "Teho (kW)", round(powerData.getMax() * 1.1, 5));
	performanceGraph.setSecondaryData(torqueData, Color(0, 0, 1), "Vääntö (Nm)", round(torqueData.getMax() * 2.5, 25));
	performanceGraph.setDomain(0, 10000);
	
	float flowRange = round(std::max(freshMixtureData.getMax(), maxExhaustData.getMax()) * 1.2, 5000);
	
	Graph flowGraph(graphFont);
	flowGraph.setPrimaryData(freshMixtureData, Color(0, 0, 1), "Imu (L / min)", flowRange);
	flowGraph.setSecondaryData(maxExhaustData, Color(1, 0, 0), "Pako (L / min)", flowRange);
	flowGraph.setDomain(0, 10000);
	
	float mixtureFlowRange = round(std::max(freshMixtureData.getMax(), usedMixtureData.getMax()) * 1.2, 5000);
	
	Graph mixtureFlowGraph(graphFont);
	mixtureFlowGraph.setPrimaryData(freshMixtureData, Color(0, 0, 1), "Tuoretta", mixtureFlowRange);
	mixtureFlowGraph.setSecondaryData(usedMixtureData, Color(1, 0, 0), "Vanhaa", mixtureFlowRange);
	mixtureFlowGraph.setDomain(0, 10000);
	
	
	while(1)
	{	
		glClearColor(1, 1, 1, 1);
		glClear(GL_COLOR_BUFFER_BIT);

		performanceGraph.draw(Vector2D(8, 8), Vector2D(500, 250));
		flowGraph.draw(Vector2D(508, 8), Vector2D(500, 250));
		mixtureFlowGraph.draw(Vector2D(508, 268), Vector2D(500, 250));
		
		try
		{
			events.processEvents();
		}
		catch(ExitException)
		{
			return 0;
		}

		SDL_GL_SwapBuffers();
	}
}
