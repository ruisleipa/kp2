#ifndef _CLUTCH_HPP
#define _CLUTCH_HPP

namespace Physics
{

class Clutch
{
	public:		
		float getTorque(float inputSpeed, float outputSpeed);

		void setUsage(float usage);
		float getUsage();
		
		Clutch(float maxTorque);	
		
	private:
		float maxTorque;
		float usage;

};

};

#endif
