#include <iostream>

#include "vehicle.hpp"
#include "engine.hpp"
#include "math_tools.hpp"

#include "sounds/sound.hpp"
#include "utils/sdl.hpp"
#include "utils/timer.hpp"
#include "graphics/color.hpp"
#include "graphics/window.hpp"
#include "graphics/fontface.hpp"
#include "events/events.hpp"

class Controller : public EventListener
{
	public:
		Controller(Engine& engine, Transmission& transmission, Clutch& clutch):
			engine(engine),
			transmission(transmission),
			clutch(clutch)
		{
			
		}

		void handleEvent(Event* event)
		{
			if(dynamic_cast<KeyDownEvent*>(event))
			{
				KeyEvent& keyEvent = *dynamic_cast<KeyDownEvent*>(event);

				if(keyEvent.getKey() == SDLK_a)
					transmission.upperGear();
				if(keyEvent.getKey() == SDLK_z)
					transmission.lowerGear();
				if(keyEvent.getKey() == SDLK_UP)
					engine.setThrottle(1.0);
				if(keyEvent.getKey() == SDLK_SPACE)
					clutch.setUsage(0.0);
				if(keyEvent.getKey() == SDLK_s)
					engine.setIgnition(true);
			}
			if(dynamic_cast<KeyUpEvent*>(event))
			{
				KeyEvent& keyEvent = *dynamic_cast<KeyUpEvent*>(event);

				if(keyEvent.getKey() == SDLK_UP)
					engine.setThrottle(0.0);
				if(keyEvent.getKey() == SDLK_SPACE)
					clutch.setUsage(1.0);
				if(keyEvent.getKey() == SDLK_s)
					engine.setIgnition(false);
			}
		}

	private:
		Engine& engine;
		Transmission& transmission;
		Clutch& clutch;
};


int main(int argc, char** argv)
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
	
	Engine engine(torqueCurve, 1000, 0.3, 7000, 2000, 0.22);
		
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

	Controller controller(engine, transmission, clutch);

	events.setEventListener(&controller);

	FontFace debugFont(window, "data/fonts/dejavusans.ttf", 24);

	Timer realTime;

	Sound engineSound;
	engineSound.load("data/sounds/s4.wav");
	engineSound.play();
	engineSound.setLooping(true);
	
	while(1)
	{
		glClear(GL_COLOR_BUFFER_BIT);

		std::wstringstream ss;

		Color(1, 1, 1).apply();

		while(vehicle.getLagInSteps(realTime.getSeconds()) > 0)
		{
			vehicle.advanceSimulation();
		}	
		
		ss << "Throttle: " << engine.getThrottle() << "\n";
		ss << "Clutch: " << clutch.getUsage() << "\n";
		ss << "Gear: " << transmission.getRatio() << "\n";
		ss << "RPM: " << vehicle.getEngineSpeed() << "\n";
		ss << "Torque: " << engine.getTorque(vehicle.getEngineSpeed() * RPM_TO_RADS) << "\n";
		ss << "Speed: " << vehicle.getVel().position * 60 * 60 / 1000 << " km/h\n";
		ss << "Gearbox out: " << vehicle.getVel().gearbox_out * RADS_TO_RPM << "\n";
		ss << "Position: " << vehicle.getPos() << " m\n";
		ss << "Lag: " << vehicle.getLagInSteps(realTime.getSeconds()) << " steps\n";

		engineSound.setPitch(1.0 + (vehicle.getEngineSpeed() - 1000.0) / 10000.0);
		engineSound.setVolume(vehicle.getEngineSpeed() / 1000.0);

		debugFont.draw(ss.str(), Vector2D(0, 0));

		

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
