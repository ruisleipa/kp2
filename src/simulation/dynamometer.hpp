#ifndef SERVER_DYNAMOMETER_HPP
#define SERVER_DYNAMOMETER_HPP

#include "utils/curve.hpp"
#include "vehicle.hpp"
#include "vehiclesimulation.hpp"

class Dynamometer
{
	public:
		void run();
		
		const Curve& getTorqueData();
		const Curve& getPowerData();
		const Curve& getIntakeData();
		const Curve& getExhaustData();
		const Curve& getBoostData();
		const Curve& getIntakeTemperatureData();
		
		Dynamometer(Vehicle& vehicle);
		
	private:
		VehicleSimulation simulation;
		
		Curve torqueData;
		Curve powerData;
		Curve intakeData;
		Curve exhaustData;
		Curve boostData;
		Curve intakeTemperatureData;
		
};

#endif
