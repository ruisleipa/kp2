#include "vehicle.hpp"
#include "math_tools.hpp"

#include <algorithm>

namespace Physics
{
const double g = 9.81;	//m/s

Vehicle::State::State():
	vehiclePosition(0.0),
	vehicleVelocity(0.0),
	vehicleAcceleration(0.0),
	engineSpeed(0.0),
	backWheelSpeed(0.0),
	frontWheelSpeed(0.0)
{
	
}

Vehicle::Derivative::Derivative():
	vehicleVelocity(0.0),
	vehicleAcceleration(0.0),
	engineAcceleration(0.0),
	backWheelAcceleration(0.0),
	frontWheelAcceleration(0.0)
{

}

Vehicle::Derivative Vehicle::Derivative::operator+(const Vehicle::Derivative& d)
{
	Vehicle::Derivative output;
	
	output.vehicleVelocity = vehicleVelocity + d.vehicleVelocity;
	output.vehicleAcceleration = vehicleAcceleration + d.vehicleAcceleration;
	output.engineAcceleration = engineAcceleration + d.engineAcceleration;
	output.backWheelAcceleration = backWheelAcceleration + d.backWheelAcceleration;
	output.frontWheelAcceleration = frontWheelAcceleration + d.frontWheelAcceleration;

	return output;
}

Vehicle::Derivative Vehicle::Derivative::operator*(double f)
{
	Vehicle::Derivative output;
	
	output.vehicleVelocity = vehicleVelocity * f;
	output.vehicleAcceleration = vehicleAcceleration * f;
	output.engineAcceleration = engineAcceleration * f;
	output.backWheelAcceleration = backWheelAcceleration * f;
	output.frontWheelAcceleration = frontWheelAcceleration * f;
	
	return output;
}

Vehicle::Vehicle(Engine& engine, Transmission& transmission, Clutch& clutch,
	Chassis& chassis, Tire& frontLeftTire, Tire& frontRightTire,
	Tire& backLeftTire, Tire& backRightTire, Brake& frontLeftBrake,
	Brake& frontRightBrake, Brake& backLeftBrake, Brake& backRightBrake,
	int ticksPerSecond
	):
	engine(engine),
	transmission(transmission),
	clutch(clutch),
	chassis(chassis),
	frontLeftTire(frontLeftTire),
	frontRightTire(frontRightTire),
	backLeftTire(backLeftTire),
	backRightTire(backRightTire),

	frontLeftBrake(frontLeftBrake),
	frontRightBrake(frontRightBrake),
	backLeftBrake(backLeftBrake),
	backRightBrake(backRightBrake),
	currentState(),
	m_brake_usage(0.0),
	step(0),
	TICKS_PER_SECOND(ticksPerSecond)
{

}

Vehicle::Derivative Vehicle::evaluate(const State& initial, double dt, const Derivative& d)
{
	State state;
	state.vehiclePosition = initial.vehiclePosition + d.vehicleVelocity * dt;
	state.vehicleVelocity = initial.vehicleVelocity + d.vehicleAcceleration * dt;
	state.vehicleAcceleration = d.vehicleAcceleration;
	state.engineSpeed = initial.engineSpeed + d.engineAcceleration * dt;
	state.backWheelSpeed = initial.backWheelSpeed + d.backWheelAcceleration * dt;
	state.frontWheelSpeed = initial.frontWheelSpeed + d.frontWheelAcceleration * dt;

	Vehicle::Derivative output = calculateAccelerations(state);
	output.vehicleVelocity = state.vehicleVelocity; 
	return output;
}

void Vehicle::advanceSimulation()
{
	double dt = 1.0 / double(TICKS_PER_SECOND);
	
	Vehicle::Derivative d = integrateRK4(dt);
	//Vehicle::Derivative d = integrateEuler(dt);	
		
	currentState.vehiclePosition = currentState.vehiclePosition + d.vehicleVelocity * dt;
	currentState.vehicleVelocity = currentState.vehicleVelocity + d.vehicleAcceleration * dt;
	currentState.vehicleAcceleration = d.vehicleAcceleration;
	currentState.engineSpeed = currentState.engineSpeed + d.engineAcceleration * dt;
	currentState.backWheelSpeed = currentState.backWheelSpeed + d.backWheelAcceleration * dt;
	currentState.frontWheelSpeed = currentState.frontWheelSpeed + d.frontWheelAcceleration * dt;
	
	if(!telemetry.is_open())
	{
		telemetry.open("data.log");
		
		telemetry << "vehiclePosition ";
		telemetry << "vehicleVelocity ";
		telemetry << "vehicleAcceleration ";
		telemetry << "engineSpeed ";
		telemetry << "frontWheelSpeed ";
		telemetry << "frontWheelAcceleration ";
		telemetry << "slipRatio ";
		telemetry << std::endl;
	}
	
	telemetry << std::fixed;
	telemetry << currentState.vehiclePosition << " ";
	telemetry << currentState.vehicleVelocity << " ";
	telemetry << currentState.vehicleAcceleration << " ";
	telemetry << currentState.engineSpeed << " ";
	telemetry << currentState.frontWheelSpeed << " ";
	telemetry << d.frontWheelAcceleration << " ";
	telemetry << (frontLeftTire.getRadius() * currentState.frontWheelSpeed - currentState.vehicleVelocity) / fabs(currentState.vehicleVelocity) << " ";
	telemetry << std::endl;
	
	step++;
}
	
Vehicle::Derivative Vehicle::integrateRK4(double dt)
{	
	Vehicle::Derivative a = evaluate(currentState, 0.0, Derivative());
	Vehicle::Derivative b = evaluate(currentState, dt * 0.5, a);
	Vehicle::Derivative c = evaluate(currentState, dt * 0.5, b);
	Vehicle::Derivative d = evaluate(currentState, dt, c);	

	return (a + (b + c) * 2.0 + d) * (1.0 / 6.0);
}
	
Vehicle::Derivative Vehicle::integrateEuler(double dt)
{	
	return evaluate(currentState, dt, Derivative());
}

Vehicle::Derivative Vehicle::calculateAccelerations(const State& state)
{
	Vehicle::Derivative d;
	
	double velocity = state.vehicleVelocity;
	double acceleration = state.vehicleAcceleration;	
	
	double weight_rear = g * chassis.massOnRear + chassis.centerOfGravityHeight /
		chassis.wheelBase * chassis.totalMass *	acceleration;
	double weight_front = chassis.totalMass * g - weight_rear;

	// absolute value of the longitudinal speed
	double absVelocity = dabs(velocity);

	double engineTorque = 0.0;
	double gearbox_overall_torque = 0.0;	
		
	engine.setSpeed(state.engineSpeed * RADS_TO_RPM);
	
	engineTorque += engine.getTorque();
	
	// determine the slip ratio, notice, that this won't get your car
	// moving if your pacjeka curve reaches zero when sr != 0
	if (absVelocity != 0.0)
	{
		frontLeftTire.setSlipRatio((frontLeftTire.getRadius() * state.frontWheelSpeed - velocity) / absVelocity);
		frontRightTire.setSlipRatio((frontRightTire.getRadius() * state.frontWheelSpeed - velocity) / absVelocity);
		backLeftTire.setSlipRatio(0);
		backRightTire.setSlipRatio(0);
	}
	else
	{
		frontLeftTire.setSlipRatio(state.frontWheelSpeed * frontLeftTire.getRadius() * 10000.0);
		frontRightTire.setSlipRatio(state.frontWheelSpeed * frontRightTire.getRadius() * 10000.0);
		backLeftTire.setSlipRatio(0);
		backRightTire.setSlipRatio(0);
	}

	// Tire.load is in kN, weight_rear & weight_front are in N
	double tractionForce = 0.0;
	
	tractionForce += backLeftTire.getFriction(0.5 * weight_rear);
	tractionForce += backRightTire.getFriction(0.5 * weight_rear);
	tractionForce += frontLeftTire.getFriction(0.5 * weight_front);
	tractionForce += frontRightTire.getFriction(0.5 * weight_front);
	
	double rollingResistanceForce = 0.0;
	
	rollingResistanceForce += backLeftTire.getRollingResistance(0.5 * weight_rear, velocity);
	rollingResistanceForce += backRightTire.getRollingResistance(0.5 * weight_rear, velocity);
	rollingResistanceForce += frontLeftTire.getRollingResistance(0.5 * weight_front, velocity);
	rollingResistanceForce += frontRightTire.getRollingResistance(0.5 * weight_front, velocity);
	
	// aerodynamic drag
	double dragForce = velocity * velocity * chassis.dragCoefficient;
	
	double driveForce = tractionForce - rollingResistanceForce - dragForce;
	
	double driveTorque = 0.0;
	
	if(!transmission.isOnNeutral())
	{
		double gearboxSpeed = state.frontWheelSpeed * transmission.getDifferentialRatio() * transmission.getRatio();
		
		double torqueTransferToTransmission = clutch.calculateTorqueTransferToTransmission(state.engineSpeed, gearboxSpeed);
		
		std::cout << clutch.calculateSlipRatio(state.engineSpeed, gearboxSpeed) << " ";
		std::cout << state.engineSpeed << " " << gearboxSpeed << " ";
		std::cout << torqueTransferToTransmission << " ";
		
		engineTorque -= torqueTransferToTransmission;
		
		driveTorque = torqueTransferToTransmission * transmission.getRatio() * transmission.getDifferentialRatio();		
	}

	double tractionTorque = tractionForce * frontLeftTire.getRadius();
	
	d.engineAcceleration = engineTorque / engine.getFlywheelInertia();	
	d.backWheelAcceleration = 0;
	d.frontWheelAcceleration = (driveTorque - tractionTorque) / (frontLeftTire.getInertia() + frontRightTire.getInertia());
	d.vehicleAcceleration = driveForce / chassis.totalMass;
	
	std::cout << state.engineSpeed * RADS_TO_RPM << " " << engineTorque << " " << driveTorque << " " << tractionTorque << std::endl;
	
	return d;
}

float Vehicle::getEngineSpeed()
{
	return currentState.engineSpeed * RADS_TO_RPM;
}

int Vehicle::getCurrentStep()
{
	return step;
}

float Vehicle::getCurrentTime()
{
	double stepTime = 1.0 / double(TICKS_PER_SECOND);
	return step * stepTime;
}

int Vehicle::getLagInSteps(double realTime)
{
	double stepTime = 1.0 / double(TICKS_PER_SECOND);
	double simulationTime = getCurrentStep() * stepTime;
	
	return int((realTime - simulationTime) / stepTime);
}

};
