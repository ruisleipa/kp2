#ifndef SERVER_DRIVER_HPP
#define SERVER_DRIVER_HPP

#include "vehiclesimulation.hpp"
#include "connection.hpp"
#include "protocol/controlstate.hpp"

class Driver
{
	public:
		void updateSimulation(float realTime);
		void setControlState(Protocol::ControlState& state);
		
		bool hasStarted();
		float getStartTime();
		bool hasFinished();
		float getFinishTime();
		float getTopSpeed();
		
		Vehicle& getVehicle();
		Connection& getConnection();
		VehicleSimulation& getSimulation();
		
		Driver(Vehicle& vehicle, Connection& connection);
		
	private:
		int decideTickRate();
		
		Vehicle& vehicle;
		Connection& connection;
		VehicleSimulation simulation;
		
		bool started;
		float startTime;
		
		bool finished;
		float finishTime;
		
		float topSpeed;
		
};

#endif
