#ifndef _CLUTCH_HPP
#define _CLUTCH_HPP

namespace Physics
{

class Clutch
{
	public:		
		float calculateTorqueTransferToTransmission(float engineSpeed, float gearboxSpeed);
		float calculateSlipRatio(float engineSpeed, float gearboxSpeed);

		void setUsage(float usage);
		float getUsage();
		
		Clutch(float maxTorque);	
		
	private:
		float maxTorque;
		float usage;

};

};

#endif
