#ifndef PHYSICS_CLUTCH_HPP
#define PHYSICS_CLUTCH_HPP

namespace Physics
{

class Clutch
{
	public:
		float calculateTransferToOutput(float input, float output, float inputInertia, float outputInertia, float inputTorque, float outputTorque, float dt);

		void setUsage(float usage);
		float getUsage();

		Clutch(float maxTorque);

	private:
		float maxTorque;
		float usage;

};

};

#endif
