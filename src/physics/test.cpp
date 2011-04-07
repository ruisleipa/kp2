#include <iostream>

#include "vehicle.hpp"
#include "engine.hpp"
#include "math_tools.hpp"

int main()
{
	std::map<int, float> torqueCurve;
	
	torqueCurve[0] = 0;
	torqueCurve[1500] = 65;
	torqueCurve[2000] = 75;
	torqueCurve[2500] = 78;
	torqueCurve[3000] = 78;
	torqueCurve[4000] = 73;
	torqueCurve[4900] = 65;
	torqueCurve[6000] = 50;
	torqueCurve[8000] = 0;
	
	Engine engine(torqueCurve, 1000, 0.15, 7000, 2000, 0.22);
		
	std::vector<float> gearRatios;
	gearRatios.push_back(-2.86);
	gearRatios.push_back(0);
	gearRatios.push_back(2.42);
	gearRatios.push_back(1.61);
	gearRatios.push_back(1.14);
	gearRatios.push_back(0.85);
	gearRatios.push_back(0.7);
	
	Transmission transmission(gearRatios, 1, 0.8, 4.22, 0.1);
	Clutch clutch(600);
	
	Chassis chassis;
	
	chassis.totalMass = 1000.0;
	chassis.massOnRear = 500;
	chassis.centerOfGravityHeight = 0.3;
	chassis.length = 2.8;
	chassis.width = 1.7;
	chassis.wheelBase = 0.0;
	chassis.dragCoefficient = 0.0;
	
	Tire tire(9, 0.3048, 0.015);
	Brake brake(0.8, 6000);
	
	Vehicle vehicle(engine, transmission, clutch, chassis, tire, tire, tire, tire, brake, brake, brake, brake);

}
