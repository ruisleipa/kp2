#include "process.hpp"

#include <cmath>
#include <iostream>

namespace Physics
{

Joules Process::getWork()
{
	State start = beginningState;
	State compressed = compressAdiabatically(start, compressionVolume);
	State heatAdded = addHeat(compressed, heatAddition);
	State expanded = compressAdiabatically(heatAdded, beginningState.volume);

	double a = heatAdded.pressure - compressed.pressure;
	double b = expanded.pressure - start.pressure;
	double h = start.volume - compressed.volume;

	return calculateTrapezoidArea(h, b, a);
}

double Process::calculateTrapezoidArea(double h, double b, double a)
{
	return (a + b) / 2.0 * h;
}

Process::Process(State beginningState, double heatAddition, double compressionVolume):
	beginningState(beginningState),
	gasConstant(8.3144621),
	heatAddition(heatAddition),
	compressionVolume(compressionVolume),
	substanceAmount(calculateSubstanceAmount())
{

}

double Process::calculateSubstanceAmount()
{
	double pv = beginningState.pressure * beginningState.volume;
	double rt = gasConstant * beginningState.temperature;

	return pv / rt;
}

Process::State Process::addHeat(const Process::State& state, double heatAddition)
{
	State newState;

	newState.volume = state.volume;
	newState.temperature = state.temperature + heatAddition;
	newState.pressure = (gasConstant * substanceAmount * newState.temperature) / newState.volume;

	return newState;
}

Process::State Process::compressAdiabatically(const Process::State &state, double newVolume)
{
	const double adiabaticIndexForDiatomicGases = 7.0 / 5.0;

	double x = state.pressure * std::pow(state.volume, adiabaticIndexForDiatomicGases);

	double newPressure = x / std::pow(newVolume, adiabaticIndexForDiatomicGases);

	State newState;

	newState.volume = newVolume;
	newState.pressure = newPressure;
	newState.temperature = (newVolume * newPressure) / (substanceAmount * gasConstant);

	return newState;
}

}
