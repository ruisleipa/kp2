#include "engine.hpp"

#include <cmath>
#include <iostream>

#include "process.hpp"

namespace Physics
{

double Engine::getTorque()
{
	const double PI = 3.14159265;

	SquareMeters cylinderArea = PI * std::pow(cylinderGeometry.bore / 2.0, 2.0);

	CubicMeters displacementVolume = cylinderArea * cylinderGeometry.stroke;
	CubicMeters compressionVolume = cylinderGeometry.compressionVolume;

	Pascals manifoldPressure = 50000.0;
	double volumetricEfficiency = 0.5;

	Process::State state;

	state.pressure = manifoldPressure * volumetricEfficiency;
	state.temperature = 273.15 + 20.0;
	state.volume = (compressionVolume + displacementVolume);

	Process process(state, 1500.0, compressionVolume);

	double work = process.getWork();

	double meanPressure = work / displacementVolume;

	double totalDisplacement = displacementVolume * double(cylinderCount);

	double torque = (totalDisplacement * meanPressure) / (PI * 2.0 * 2.0);

//	std::cout << "displacement: " << displacementVolume * 1000.0 << " liters" << std::endl;
//	std::cout << "cylinders: " << cylinderCount << std::endl;
//	std::cout << "compressionRatio: " << (displacementVolume + compressionVolume) / compressionVolume << ":1" << std::endl;
//	std::cout << "displacementVolume: " << displacementVolume << " m^3" << std::endl;
//	std::cout << "manifoldPressure: " << manifoldPressure << " Pa" << std::endl;
//	std::cout << "volumetricEfficiency: " << volumetricEfficiency * 100.0 << " %" << std::endl;
//	std::cout << "sweptVolume: " << displacementVolume << " m^3" << std::endl;
//	std::cout << "work: " << work << " J" << std::endl;
//	std::cout << "meanPressure: " << meanPressure << " kPa" << std::endl;
//	std::cout << "torque: " << torque << " Nm" << std::endl;

	return torque;
}

Engine::Engine(int cylinderCount, CylinderGeometry cylinderGeometry):
	cylinderCount(cylinderCount),
	cylinderGeometry(cylinderGeometry)
{
}

}
