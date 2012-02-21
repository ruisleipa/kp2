#ifndef _MATH_TOOLS_HPP
#define _MATH_TOOLS_HPP
#include <cmath>
#include <cstdlib>

template <typename flt>
class tVector
{
	public:	
		tVector();
		tVector(flt, flt, flt);
		~tVector();
		flt Length();
		tVector operator=(const tVector &);
		tVector operator+(const tVector &);
		tVector operator-(const tVector &);
		tVector operator/(flt);
		tVector operator*(flt);
		tVector operator+=(const tVector &);
		tVector operator-=(const tVector &);
		tVector operator/=(flt);
		tVector operator*=(flt);
		flt DotProduct(const tVector &);
		tVector CrossProduct(const tVector &);
		flt x, y, z;
};

template <typename flt>
tVector<flt>::tVector()
{
	x = y = z = 0.0;
}

template <typename flt>
tVector<flt>::tVector(flt i, flt j, flt k)
{
	x = i; y = j; z = k;
}

template <typename flt>
tVector<flt>::~tVector()
{
}

template <typename flt>
flt tVector<flt>::Length()
{
	//return sqrt(this->DotProduct(*this));
	return sqrt(x*x + y*y + z*z);
}

template <typename flt>
tVector<flt> tVector<flt>::operator=(const tVector & p)
{
	x = p.x;
	y = p.y;
	z = p.z;
	return *this;
}

template <typename flt>
tVector<flt> tVector<flt>::operator+(const tVector & p)
{
	return tVector(x + p.x, y + p.y, z + p.z);
}

template <typename flt>
tVector<flt> tVector<flt>::operator-(const tVector & p)
{
	return tVector(x - p.x, y - p.y, z - p.z);
}

template <typename flt>
tVector<flt> tVector<flt>::operator-=(const tVector & p)
{
	x -= p.x;
	y -= p.y;
	z -= p.z;
	return *this;
}

template <typename flt>
tVector<flt> tVector<flt>::operator+=(const tVector & p)
{
	x += p.x;
	y += p.y;
	z += p.z;
	return *this;
}

template <typename flt>
tVector<flt> tVector<flt>::operator*=(flt q)
{
	x *= q;
	y *= q;
	z *= q;
	return *this;
}

template <typename flt>
tVector<flt> tVector<flt>::operator/=(flt q)
{
	x /= q;
	y /= q;
	z /= q;
	return *this;
}

template <typename flt>
tVector<flt> tVector<flt>::operator/(flt q)
{
	return (*this) * (1.0 / q); 
}

template <typename flt>
tVector<flt> tVector<flt>::operator*(flt q)
{
	return tVector(x * q, y * q, z * q);
}

template <typename flt>
flt tVector<flt>::DotProduct(const tVector & p)
{
	return (x * p.x + y * p.y + z * p.z);
}

template <typename flt>
tVector<flt> tVector<flt>::CrossProduct(const tVector & p)
{
	return tVector(y * p.z - z * p.y, z * p.x - x * p.z, x * p.y - y * p.x);
}

struct vector_2d_float
{
	float x, y;
};

struct vector_2d_double
{
	double x, y;
};

struct vector_3d_float
{
	float x, y, z;
};

struct vector_3d_double
{
	double x, y, z;
};

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

// round a floating point number to next greater or equal integer number
inline int round(float r)
{
	return int (0.5f + r);
}

// find the next greater or equal power of 2
inline unsigned int pot( unsigned int n )
{
	unsigned int i = 1;
	while (i < n)
	i <<= 1;

	return i;
}


inline bool Line_Isect(tVector<float> a1, tVector<float> a2, tVector<float> b1, tVector<float> b2, tVector<float> *r)
{
	//std::cerr << "(" << a1.x << "," << a1.y << ")-(" << a2.x << "," << a2.y << ") x (" << b1.x << "," << b1.y << ")-(" << b2.x << "," << b2.y << ")\n";

	float C, dax, day, dbx, dby, s, t;

	dax = a2.x - a1.x;
	day = a2.y - a1.y;
	dbx = b2.x - b1.x;
	dby = b2.y - b1.y;

	C = dax * dby - day * dbx;

	if (C)
	{
		s = (dbx * (a1.y - b1.y) - dby * (a1.x - b1.x)) / C;
		t = (dax * (a1.y - b1.y) - day * (a1.x - b1.x)) / C;
	}
	else
		return false;

	if ((s < 0.0f) || (s > 1.0f) || (t < 0.0f) || (t > 1.0f))
		return false;
	
	
	r->x = a1.x + s * dax;
	r->y = a1.y + t * day;

	return true;
	
}

inline bool Line_Isect2(vector_2d_float a1, vector_2d_float a2, vector_2d_float b1, vector_2d_float b2, vector_2d_float* r)
{
	//std::cerr << "(" << a1.x << "," << a1.y << ")-(" << a2.x << "," << a2.y << ") x (" << b1.x << "," << b1.y << ")-(" << b2.x << "," << b2.y << ")\n";
	float C, dax, day, dbx, dby;

	dax = a2.x - a1.x;
	day = a2.y - a1.y;
	dbx = b2.x - b1.x;
	dby = b2.y - b1.y;
	
	C = day * dbx - dax * dby;
	
	if (C)
		r->x = (dax * dbx) * (b1.y - a1.y) / C;
	else
		return false;

	if (dax)
		r->y = a1.y + r->x * day / dax;
	else
		r->y = b1.y + r->x * dby / dbx;

	if ((r->x < a1.x) && (r->x < a2.x))
		return false;
	if ((r->x > a1.x) && (r->x > a2.x))
		return false;
	if ((r->x < b1.x) && (r->x < b2.x))
		return false;
	if ((r->x > b1.x) && (r->x > b2.x))
		return false;
	if ((r->y < a1.y) && (r->y < a2.y))
		return false;
	if ((r->y > a1.y) && (r->y > a2.y))
		return false;
	if ((r->y < b1.y) && (r->y < b2.y))
		return false;
	if ((r->y > b1.y) && (r->y > b2.y))
		return false;

	return true;
}

template<class type1>
type1 MinVal(type1* arr, int n)
{
    type1 smallest = arr[0];
    for(int i = 1; i < n; i++)
    {
        if(arr[i] < smallest)
            smallest = arr[i];
    }
    return smallest;
}


template<class type1>
type1 MaxVal(type1* arr, int n)
{
    type1 biggest = arr[0];
    for(int i = 1; i < n; i++)
    {
        if(arr[i] > biggest)
            biggest = arr[i];
    }
    return biggest;
}



const float PI = 3.14159265f;
const float RAD = PI / 180.0f;
const float RADS_TO_RPM = 60.0f / (2.0f * PI);
const float RPM_TO_RADS = (2.0f * PI) / 60.0f;
#endif
