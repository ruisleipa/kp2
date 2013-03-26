#ifndef PHYSICS_PROCESS_HPP
#define PHYSICS_PROCESS_HPP

#include "units.hpp"

namespace Physics
{

class Process
{
	public:
		class State
		{
			public:
				Kelvins temperature;
				CubicMeters volume;
				Pascals pressure;
		};

		Joules getWork();

		Process(State beginningState, double heatAddition, double compressionVolume);

		double calculateTrapezoidArea(double h, double b, double a);
		Process::State addHeat(const Process::State &state, double headAddition);
	private:
		double calculateSubstanceAmount();
		State compressAdiabatically(const State& state, double newVolume);

		const State beginningState;
		const double gasConstant;
		const double heatAddition;
		const double compressionVolume;
		const double substanceAmount;
};

};

#endif // GAS_HPP
