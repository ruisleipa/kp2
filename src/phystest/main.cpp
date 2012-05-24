#include <fstream>
#include <iostream>
#include "game/engine.hpp"
#include "physics/math_tools.hpp"
#include "physics/engine.hpp"
#include "physics/starter.hpp"
#include "physics/flywheel.hpp"
#include "physics/clutch.hpp"
#include "physics/axle.hpp"

int main(int argc,char** argv)
{
	Json::Value engineJson;

	std::ifstream("engine.json") >> engineJson;

	Game::Engine enginePart(engineJson);

	Physics::Engine engine(enginePart);
	Physics::Starter starter;
	Physics::Flywheel flywheel;
	Physics::Clutch clutch(100);
	Physics::Axle axle(0.1);

	double dt = 0.1d;
	double t = 0.0d;

	double vEngine = 0.0d;
	double vDrivetrain = 0.0d;

	std::cout << "t" << "\t";
	std::cout << "vEngine" << "\t";
	std::cout << "engineTorque" << "\t";
	std::cout << "engineInertia" << "\t";
	std::cout << "vDrivetrain" << "\t";
	std::cout << "drivetrainTorque" << "\t";
	std::cout << "drivetrainInertia" << "\t";
	std::cout << std::endl;

	engine.setThrottle(1.0);
	starter.setRunning(true);

	while(t < 10)
	{
		t += dt;

		if(vEngine * RADS_TO_RPM > 1000)
			starter.setRunning(false);

		if(vEngine * RADS_TO_RPM > 2500)
		{
			clutch.setUsage(1.0);
		}

		double engineTorque = 0.0d;

		engineTorque += engine.getTorque(vEngine);
		engineTorque += starter.getTorque(vEngine);
		engineTorque += flywheel.getTorque();

		double engineInertia = 0.0d;

		engineInertia += engine.getInertia();
		engineInertia += starter.getInertia();
		engineInertia += flywheel.getInertia();

		double drivetrainTorque = 0.0d;

		double drivetrainInertia = 0.0d;

		drivetrainInertia += axle.getInertia();

		double clutchTransferToOutput = clutch.calculateTransferToOutput(vEngine, vDrivetrain, engineInertia, drivetrainInertia, engineTorque, drivetrainTorque, dt);

		engineTorque -= clutchTransferToOutput;
		drivetrainTorque += clutchTransferToOutput;

		vEngine += engineTorque / engineInertia * dt;
		vDrivetrain += drivetrainTorque / drivetrainInertia * dt;

		std::cout << t << "\t";
		std::cout << vEngine * RADS_TO_RPM << "\t";
		std::cout << engineTorque << "\t";
		std::cout << engineInertia << "\t";
		std::cout << vDrivetrain * RADS_TO_RPM << "\t";
		std::cout << drivetrainTorque << "\t";
		std::cout << drivetrainInertia << "\t";
		std::cout << std::endl;
	}
}

