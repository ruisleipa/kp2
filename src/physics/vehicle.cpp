#include "vehicle.hpp"
#include "math_tools.hpp"

const int TICKS_PER_SECOND = 300;

const double g = 9.81;	//m/s

Vehicle::State::State():
	vehicle_pos(0.0, 0.0, 0.0),
	m_vehicle_angle(0.0),
	m_flywheel(0.0),
	gearbox_out(0.0),
	m_planet_gear(0.0),
	m_f_l_tire(0.0),
	m_f_r_tire(0.0)
{
	
}

void Vehicle::State::add(double factor, State& dx)
{
	vehicle_pos += dx.vehicle_pos * factor;
	m_vehicle_angle += dx.m_vehicle_angle * factor;
	m_flywheel += dx.m_flywheel * factor;
	gearbox_out += dx.gearbox_out * factor;
	m_planet_gear += dx.m_planet_gear * factor;
	m_f_l_tire += dx.m_f_l_tire * factor;
	m_f_r_tire += dx.m_f_r_tire * factor;
}

Vehicle::Vehicle(Engine& engine, Gearbox& gearbox, Clutch& clutch,
	Chassis& chassis, Tire& frontLeftTire, Tire& frontRightTire,
	Tire& backLeftTire, Tire& backRightTire, Brake& frontLeftBrake,
	Brake& frontRightBrake,	Brake& backLeftBrake, Brake& backRightBrake):
	engine(engine),
	gearbox(gearbox),
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
	m_current_x(),
	m_current_v(),
	m_current_a()
{

	m_brake_usage=0;
	clutch_usage=1;
	m_current_gear=gearbox.getNeutralGear();
	
	return;
}

void Vehicle::advanceSimulation()
{
	double time_chunk = 1.0 / double(TICKS_PER_SECOND);
	
	getDerivates(&m_current_x, &m_current_v, &m_current_a);
	m_current_v.add(time_chunk, m_current_a);
	m_current_x.add(time_chunk, m_current_v);
}

void Vehicle::getDerivates(State* p0, State* v0, State* a0)
{
	double velocity = v0->position;
	double acceleration = a0->position;	
	
	double weight_rear = g * chassis.getRearMass() + chassis.getCenterOfGravityHeight() /
		chassis.getWheelbase() * chassis.getTotalMass() *
								acceleration;
	double weight_front = chassis.getTotalMass() * g - weight_rear;

	double r_l_tire = v0->gearbox_out /	gearbox.getDifferentialRatio() - v0->m_planet_gear;
	double r_r_tire = r_l_tire + 2.0 * v0->m_planet_gear;

	// absolute value of the longitudinal speed
	double _abs_veh_vel_ = dabs(velocity);

	double engine_overall_torque = 0.0;
	double gearbox_overall_torque = 0.0;	
		
	// Consider how to get the gear ratio
	if (m_current_gear!=gearbox.getNeutralGear())
	{
		double clutch_torque_deliver = clutch.getTorque(clutch_usage,v0->gearbox_out * gearbox.getRatio(m_current_gear), v0->m_flywheel);
		gearbox_overall_torque = -clutch_torque_deliver * gearbox.getRatio(m_current_gear);
		// check the sign
		engine_overall_torque += clutch_torque_deliver;
	}

	engine_overall_torque += m_engine.getTorque(v0->m_flywheel);
	
	// determine the slip ratio, notice, that this won't get your car
	// moving if your pacjeka curve reaches zero when sr != 0
	if (_abs_veh_vel_ != 0.0)
	{
		frontLeftTire.m_sratio = 100.0 *
			(frontLeftTire.getRadius() * v0->m_f_l_tire -
					 vehicle_speed) / _abs_veh_vel_;
		frontRightTire.m_sratio = 100.0 *
			(frontRightTire.getRadius() * v0->m_f_r_tire -
			 		vehicle_speed) / _abs_veh_vel_;
		backLeftTire.m_sratio = 100.0 *
				(backLeftTire.getRadius() * r_l_tire -
				 		vehicle_speed) / _abs_veh_vel_;
		backRightTire.m_sratio = 100.0 *
				(backRightTire.getRadius() * r_r_tire -
				 		vehicle_speed) / _abs_veh_vel_;
	}
	else
	{
		frontLeftTire.m_sratio = v0->m_f_l_tire *
				frontLeftTire.getRadius() * 10000.0;
		frontRightTire.m_sratio = v0->m_f_r_tire *
				frontRightTire.getRadius() * 10000.0;
		backLeftTire.m_sratio = r_l_tire *
				backLeftTire.getRadius() * 10000.0;
		backRightTire.m_sratio = r_r_tire *
				backRightTire.getRadius() * 10000.0;
	}
	
	// Tire.load is in kN, weight_rear & weight_front are in N
	double r_l_traction_force = backLeftTire.getFriction(0.5 * weight_rear);
	double r_r_traction_force = backRightTire.getFriction(0.5 * weight_rear);
	double f_l_traction_force = frontLeftTire.getFriction(0.5 * weight_front);
	double f_r_traction_force = frontRightTire.getFriction(0.5 * weight_front);

	double total_force = r_l_traction_force + r_r_traction_force + f_l_traction_force + f_r_traction_force;
	total_force -= backLeftTire.getRollingResist(0.5 * weight_rear, vehicle_speed);
	total_force -= backRightTire.getRollingResist(0.5 * weight_rear, vehicle_speed);
	total_force -= frontLeftTire.getRollingResist(0.5 * weight_front, vehicle_speed);
	total_force -= frontRightTire.getRollingResist(0.5 * weight_front, vehicle_speed);
	// aerodynamic drag
	total_force += vehicle_speed * vehicle_speed * chassis.getAeroDrag();

	double rear_left_trq = backLeftBrake.getTorque(m_brake_usage,r_l_tire) - backLeftTire.getRadius() * r_l_traction_force;
	double rear_right_trq = backRightBrake.getTorque(m_brake_usage,r_r_tire) - backRightTire.getRadius() * r_r_traction_force;

	double front_left_trq =	frontLeftBrake.getTorque(m_brake_usage,v0->m_f_l_tire) - frontLeftTire.getRadius() * f_l_traction_force;
	double front_right_trq = frontRightBrake.getTorque(m_brake_usage,v0->m_f_r_tire) - frontRightTire.getRadius() * f_r_traction_force;

	// + diff_lock(v0.m_planet_gear);
	double rearaxle_trq = rear_right_trq - rear_left_trq;

	// this model needs to do with gearbox loss of energy!
	gearbox_overall_torque += (rear_left_trq + rear_right_trq) / gearbox.getDifferentialRatio();

	
	
	
	a0->m_flywheel = engine_overall_torque / m_engine.getFlywheelInertia();
	a0->gearbox_out = gearbox_overall_torque /
		(
		 	gearbox.getDriveshaftInertia() +
		 	(
			 	backLeftTire.getInertia() +
				backRightTire.getInertia()
			) /
			gearbox.getDifferentialRatio()
		);
	
	
	
	a0->m_planet_gear = rearaxle_trq /
				(backLeftTire.getInertia() +
					 backRightTire.getInertia());
	a0->m_f_l_tire = front_left_trq / frontLeftTire.getInertia();
	a0->m_f_r_tire = front_right_trq / frontRightTire.getInertia();
	a0->vehicle_pos = vehicle_alignment * (total_force /
						chassis.getTotalMass());
}


void Vehicle::setBrakeUsage(float usage)
{
	m_brake_usage=usage;
}

float Vehicle::getBrakeUsage()
{
	return m_brake_usage;
}

void Vehicle::setThrottle(float throttle)
{
	m_throttle=throttle;
}

float Vehicle::getThrottle()
{
	return m_throttle;
}

void Vehicle::setClutchUsage(float usage)
{
	clutch_usage=usage;
}

float Vehicle::getClutchUsage()
{
	return clutch_usage;
}

void Vehicle::setIgnition(bool ignition)
{
	m_ignition=ignition;
}

bool Vehicle::getIgnition()
{
	return m_ignition;
}

void Vehicle::setGear(int gear)
{
	m_current_gear=gear;
}

int Vehicle::getGear()
{
	return m_current_gear;
}

float Vehicle::getEngineSpeed()
{
	return m_current_v.m_flywheel * RADS_TO_RPM;
}

int Vehicle::getCurrentStep()
{
	return step;
}

int Vehicle::getLagInSteps(double realTime)
{
	double stepTime = 1.0 / double(TICKS_PER_SECOND);
	double simulationTime = getCurrentStep() * stepTime;
	
	return int((realTime - simulationTime) / stepTime);
}
