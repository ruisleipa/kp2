#include "vehicle.hpp"
#include "math_tools.hpp"
#include "shared/inifile.hpp"
#include "timer.hpp"

#ifdef _THREAD_DEBUG_
#define TTICKS_COUNT 10000
#endif

#define ENGINE_ITERATIONS 300
const double g = 9.81;	//m/s

Vehicle::State::State()
{
}

Vehicle::State::State(double initval):vehicle_pos(initval, initval, initval)
{
	m_vehicle_angle = 0;
	m_flywheel = initval;
	m_gearbox_out = initval;
	m_planet_gear = initval;
	m_f_l_tire = initval;
	m_f_r_tire = initval;
}

Vehicle::State Vehicle::State::operator*(double factor)
{
	Vehicle::State tmp;
	tmp.vehicle_pos = vehicle_pos * factor;
	tmp.m_vehicle_angle = m_vehicle_angle * factor;
	tmp.m_flywheel = m_flywheel * factor;
	tmp.m_gearbox_out = m_gearbox_out * factor;
	tmp.m_planet_gear = m_planet_gear * factor;
	tmp.m_f_l_tire = m_f_l_tire * factor;
	tmp.m_f_r_tire = m_f_r_tire * factor;
	return tmp;
}

Vehicle::State& Vehicle::State::operator+=(State& inc)
{
	vehicle_pos += inc.vehicle_pos;
	m_vehicle_angle += inc.m_vehicle_angle;
	m_flywheel += inc.m_flywheel;
	m_gearbox_out += inc.m_gearbox_out;
	m_planet_gear += inc.m_planet_gear;
	m_f_l_tire += inc.m_f_l_tire;
	m_f_r_tire += inc.m_f_r_tire;
	return *this;
}
void Vehicle::State::add(double factor, State& dx)
{
	vehicle_pos += dx.vehicle_pos * factor;
	m_vehicle_angle += dx.m_vehicle_angle * factor;
	m_flywheel += dx.m_flywheel * factor;
	m_gearbox_out += dx.m_gearbox_out * factor;
	m_planet_gear += dx.m_planet_gear * factor;
	m_f_l_tire += dx.m_f_l_tire * factor;
	m_f_r_tire += dx.m_f_r_tire * factor;
}

Vehicle::Vehicle(Engine engine, Gearbox gearbox, Clutch clutch, Chassis chassis,
		Tire fltire, Tire frtire, Tire bltire, Tire brtire, 
		Brake flbrake, Brake frbrake, Brake blbrake, Brake brbrake):
	m_current_x(0.0),
	m_current_v(0.0),
	m_current_a(0.0)
{
	m_engine = engine;
	m_gearbox = gearbox;
	m_clutch = clutch;
	m_chassis = chassis;

	m_tires[FRONT_LEFT] = fltire;
	m_tires[FRONT_RIGHT] = frtire;
	m_tires[REAR_LEFT] = bltire;
	m_tires[REAR_RIGHT] = brtire;

	m_brakes[FRONT_LEFT] = flbrake;
	m_brakes[FRONT_RIGHT] = frbrake;
	m_brakes[REAR_LEFT] = blbrake;
	m_brakes[REAR_RIGHT] = brbrake;

	m_log_telemetry = false;
	m_simulate = false;
	
	m_brake_usage=0;
	m_throttle=0;
	m_clutch_usage=1;
	m_ignition=false;
	m_current_gear=m_gearbox.getNeutralGear();
	
	return;
}

Vehicle::~Vehicle()
{
	toggleTelemetry(false);
}

int Vehicle::load(const std::string& filename)
{
	IniFile in;
	if (in.load(filename))
	{
		std::cerr << "Unable to open \"" << filename << "\"\n";
		return -1;
	}
	
	if (m_log_telemetry)
	{
		toggleTelemetry(true);
	}

	return 0;
}

int Vehicle::toggleTelemetry(bool on)
{
	if (on == true && !m_tel_out.is_open())
	{
		m_tel_out.open("telemetry",
				std::ios::out|std::ios::app|std::ios::binary);
		if (!m_tel_out.is_open())
		{
			std::cerr << "couldn't open telemetryfile" << std::endl;
			return -1;
		}
		m_log_telemetry = true;	
	}
	else if (on == false && m_tel_out.is_open())
	{
		m_tel_out.close();
	}

	return 0;
}

int physics(void* data)
{
	#ifdef DEBUG_MODE
	long int loops = 0;
	#endif
	/* this function reads these members:
		inputs
		timer
	   this function writes to these members:
		Current_p
		m_current_v
		m_current_a
	*/
	Vehicle& dstvehicle = *(reinterpret_cast<Vehicle*>(data));
	
	Vehicle::State m_current_x = dstvehicle.m_current_x;	//positions
	Vehicle::State m_current_v = dstvehicle.m_current_v;	//speeds
	Vehicle::State m_current_a = dstvehicle.m_current_a;	//accelerations

	#ifdef _THREAD_DEBUG_
	double time_ticks[TTICKS_COUNT];
	long int frame = 0;
	#endif

	timer tmr;
	double time_chunk;
	double real_lag = 0.0;
	double last_time;
	double start_time = last_time = tmr.get_seconds();
	while (dstvehicle.m_simulate)
	{		
		time_chunk = real_lag / ENGINE_ITERATIONS;
		
		for (int i = 0; i < ENGINE_ITERATIONS; ++i)
		{
			dstvehicle.getDerivates(&m_current_x, &m_current_v,
								&m_current_a);
			m_current_v.add(time_chunk, m_current_a);

			if(fabs(m_current_v.vehicle_pos.y) > 0.09)
				m_current_x.add(time_chunk, m_current_v);
		}
	
		dstvehicle.m_current_x = m_current_x;
		dstvehicle.m_current_v = m_current_v;
		dstvehicle.m_current_a = m_current_a;
		
		real_lag = tmr.get_seconds() - last_time;
		last_time += real_lag;
		
		#ifdef _THREAD_DEBUG_
		if (frame < TTICKS_COUNT)
		{
			time_ticks[frame] = real_lag;
			++frame;
		}
		#endif
		
		#ifdef DEBUG_MODE
		++loops;
		#endif
	}

	#ifdef DEBUG_MODE
	std::cout << "Thread finished, average execution rate was " <<
	0.001 * double (loops * ENGINE_ITERATIONS) /
	(last_time - start_time) << "kHz\n";
	#endif
	
	#ifdef _THREAD_DEBUG_
	std::ofstream f("ticks.txt");
	for (int i = 0; i < frame; ++i)
		f << time_ticks[i] << '\xA';
	#endif
	
	return 0;
}

int Vehicle::startThread()
{
	if (m_simulate)
		return -1;
	
	m_simulate = true;
	m_enginethread=Thread(physics);
	m_enginethread.run(this);

	#ifdef DEBUG_MODE
	std::cout << "Thread #" << m_enginethread.getId() << " started\n";
	#endif

	return 0;
}

int Vehicle::stopThread()
{
	int retval;
	m_simulate = false;

	#ifdef DEBUG_MODE
	std::cout << "Waiting thread #" << m_enginethread.getId() <<
	" to finish\n";
	#endif

	retval = m_enginethread.wait();
	return retval;
}

void Vehicle::getDerivates(State* p0, State* v0, State* a0)
{
	// Use previous first and second order State derivates
	// to solve current second order State derivates
	tVector<double> vehicle_alignment(0,1, 0.0);
	// vehicle's longitudinal speed
	double vehicle_speed = v0->vehicle_pos.DotProduct(vehicle_alignment);
	// vehicle's longitudinal acceleration
	double vehicle_acc = a0->vehicle_pos.DotProduct(vehicle_alignment);

	double engine_overall_torque = 0.0;
	double gearbox_overall_torque = 0.0;

	double weight_rear = g * m_chassis.getRearMass() + m_chassis.getCenterOfGravityHeight() /
		m_chassis.getWheelbase() * m_chassis.getTotalMass() *
								vehicle_acc;
	double weight_front = m_chassis.getTotalMass() * g - weight_rear;

	double r_l_tire = v0->m_gearbox_out /
			m_gearbox.getDifferentialRatio() - v0->m_planet_gear;
	double r_r_tire = r_l_tire + 2.0 * v0->m_planet_gear;

	// absolute value of the longitudinal speed
	double _abs_veh_vel_ = dabs(vehicle_speed);

	// overall_ratio = m_gearbox.differential_ratio * m_gearbox.ratio();
	// Consider how to get the gear ratio
	if (m_current_gear!=m_gearbox.getNeutralGear())
	{
		double clutch_torque_deliver =
			m_clutch.getTorque(m_clutch_usage,v0->m_gearbox_out *
			m_gearbox.getRatio(m_current_gear), v0->m_flywheel);
		gearbox_overall_torque = -clutch_torque_deliver *
					m_gearbox.getRatio(m_current_gear);
		// check the sign
		engine_overall_torque += clutch_torque_deliver;
	}

	engine_overall_torque += m_engine.getTorque(m_throttle,m_ignition,v0->m_flywheel);
	
	// determine the slip ratio, notice, that this won't get your car
	// moving if your pacjeka curve reaches zero when sr != 0
	if (_abs_veh_vel_ != 0.0)
	{
		m_tires[FRONT_LEFT].m_sratio = 100.0 *
			(m_tires[FRONT_LEFT].getRadius() * v0->m_f_l_tire -
					 vehicle_speed) / _abs_veh_vel_;
		m_tires[FRONT_RIGHT].m_sratio = 100.0 *
			(m_tires[FRONT_RIGHT].getRadius() * v0->m_f_r_tire -
			 		vehicle_speed) / _abs_veh_vel_;
		m_tires[REAR_LEFT].m_sratio = 100.0 *
				(m_tires[REAR_LEFT].getRadius() * r_l_tire -
				 		vehicle_speed) / _abs_veh_vel_;
		m_tires[REAR_RIGHT].m_sratio = 100.0 *
				(m_tires[REAR_RIGHT].getRadius() * r_r_tire -
				 		vehicle_speed) / _abs_veh_vel_;
	}
	else
	{
		m_tires[FRONT_LEFT].m_sratio = v0->m_f_l_tire *
				m_tires[FRONT_LEFT].getRadius() * 10000.0;
		m_tires[FRONT_RIGHT].m_sratio = v0->m_f_r_tire *
				m_tires[FRONT_RIGHT].getRadius() * 10000.0;
		m_tires[REAR_LEFT].m_sratio = r_l_tire *
				m_tires[REAR_LEFT].getRadius() * 10000.0;
		m_tires[REAR_RIGHT].m_sratio = r_r_tire *
				m_tires[REAR_RIGHT].getRadius() * 10000.0;
	}
	
	// Tire.load is in kN, weight_rear & weight_front are in N
	double r_l_traction_force = m_tires[REAR_LEFT].getFriction
							(0.5 * weight_rear);
	double r_r_traction_force = m_tires[REAR_RIGHT].getFriction
							(0.5 * weight_rear);
	double f_l_traction_force = m_tires[FRONT_LEFT].getFriction
							(0.5 * weight_front);
	double f_r_traction_force = m_tires[FRONT_RIGHT].getFriction
							(0.5 * weight_front);

	double total_force = r_l_traction_force + r_r_traction_force +
				f_l_traction_force + f_r_traction_force;
	total_force -= m_tires[REAR_LEFT].getRollingResist
					(0.5 * weight_rear, vehicle_speed);
	total_force -= m_tires[REAR_RIGHT].getRollingResist
					(0.5 * weight_rear, vehicle_speed);
	total_force -= m_tires[FRONT_LEFT].getRollingResist
					(0.5 * weight_front, vehicle_speed);
	total_force -= m_tires[FRONT_RIGHT].getRollingResist
					(0.5 * weight_front, vehicle_speed);
	// aerodynamic drag
	total_force += vehicle_speed * vehicle_speed * m_chassis.getAeroDrag();

	double rear_left_trq = m_brakes[REAR_LEFT].getTorque(m_brake_usage,r_l_tire)
			- m_tires[REAR_LEFT].getRadius() * r_l_traction_force;
	double rear_right_trq = m_brakes[REAR_RIGHT].getTorque(m_brake_usage,r_r_tire)
	       		- m_tires[REAR_RIGHT].getRadius() * r_r_traction_force;

	double front_left_trq =
		m_brakes[FRONT_LEFT].getTorque(m_brake_usage,v0->m_f_l_tire) -
			m_tires[FRONT_LEFT].getRadius() * f_l_traction_force;
	double front_right_trq =
		m_brakes[FRONT_RIGHT].getTorque(m_brake_usage,v0->m_f_r_tire) -
			m_tires[FRONT_RIGHT].getRadius() * f_r_traction_force;

	// + diff_lock(v0.m_planet_gear);
	double rearaxle_trq = rear_right_trq - rear_left_trq;

	// this model needs to do with m_gearbox loss of energy!
	gearbox_overall_torque += (rear_left_trq + rear_right_trq) /
	    				m_gearbox.getDifferentialRatio();

	a0->m_flywheel = engine_overall_torque / m_engine.getFlywheelInertia();
	a0->m_gearbox_out = gearbox_overall_torque /
		(
		 	m_gearbox.getDriveshaftInertia() +
		 	(
			 	m_tires[REAR_LEFT].getInertia() +
				m_tires[REAR_RIGHT].getInertia()
			) /
			m_gearbox.getDifferentialRatio()
		);
	a0->m_planet_gear = rearaxle_trq /
				(m_tires[REAR_LEFT].getInertia() +
					 m_tires[REAR_RIGHT].getInertia());
	a0->m_f_l_tire = front_left_trq / m_tires[FRONT_LEFT].getInertia();
	a0->m_f_r_tire = front_right_trq / m_tires[FRONT_RIGHT].getInertia();
	a0->vehicle_pos = vehicle_alignment * (total_force /
						m_chassis.getTotalMass());
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
	m_clutch_usage=usage;
}

float Vehicle::getClutchUsage()
{
	return m_clutch_usage;
}

void Vehicle::setIgnition(bool ignition)
{
	m_ignition=ignition;
}

float Vehicle::getIgnition()
{
	return m_ignition;
}

void Vehicle::setGear(int gear)
{
	m_current_gear=gear;
}

float Vehicle::getGear()
{
	return m_current_gear;
}

float Vehicle::getEngineSpeed()
{
	return m_current_v.m_flywheel * RADS_TO_RPM;
}




