#ifndef PHYSICS_MATH_TOOLS_HPP
#define PHYSICS_MATH_TOOLS_HPP

// get the sign
inline double sgn(double value)
{
    if(value > 0.0)
        return 1.0;
    else if(value < 0.0)
        return -1.0;
    else
        return 0.0;
}

// dabs(x) = |x|
inline double dabs(double x)
{
	if (x < 0.0)
		return -x;
	else
		return x;
}

const float PI = 3.14159265f;
const float RAD = PI / 180.0f;
const float RADS_TO_RPM = 60.0f / (2.0f * PI);
const float RPM_TO_RADS = (2.0f * PI) / 60.0f;

#endif
