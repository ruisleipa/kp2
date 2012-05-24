#include "clutch.hpp"
#include "math_tools.hpp"

#include <algorithm>
#include <cmath>

namespace Physics
{

float Clutch::calculateTransferToOutput(float input, float output, float inputInertia, float outputInertia, float inputTorque, float outputTorque, float dt)
{
	float targetSpeed = (input * inputInertia + output * outputInertia) / (inputInertia + outputInertia);

	float torqueAverage = (inputTorque * inputInertia + outputTorque * outputInertia) / (inputInertia + outputInertia);

	float maxTransfer = ((targetSpeed - output) * outputInertia) / dt + (torqueAverage);

	float torque = std::min(dabs(maxTransfer), double(maxTorque)) * sgn(maxTransfer);

	return torque * pow(usage, 3);
}

void Clutch::setUsage(float usage)
{
	this->usage = usage;
}

float Clutch::getUsage()
{
	return usage;
}

Clutch::Clutch(float maxTorque):
	maxTorque(maxTorque),
	usage(0)
{

}

};

