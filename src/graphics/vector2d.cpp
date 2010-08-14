#include "vector2d.hpp"

Vector2D::Vector2D()
{
	m_x=0;
	m_y=0;
}

Vector2D::Vector2D(float x,float y)
{
	m_x=x;
	m_y=y;
}

Vector2D Vector2D::operator+(const Vector2D& a) const
{
	return Vector2D(a.m_x+m_x,a.m_y+m_y);
}

Vector2D Vector2D::operator-(const Vector2D& a) const
{
	return Vector2D(m_x-a.m_x,m_y-a.m_y);	
}

Vector2D Vector2D::operator*(const Vector2D& a) const
{
	return Vector2D(m_x*a.m_x,m_y*a.m_y);	
}

Vector2D Vector2D::operator/(const Vector2D& a) const
{
	return Vector2D(m_x/a.m_x,m_y/a.m_y);	
}

Vector2D Vector2D::operator/(float a) const
{
	if(!a)
		a=1;

	return Vector2D(m_x/a,m_y/a);	
}

Vector2D Vector2D::operator*(float a) const
{
	return Vector2D(m_x*a,m_y*a);	
}



Vector2D& Vector2D::operator+=(const Vector2D& a)
{
	m_x+=a.m_x;
	m_y+=a.m_y;

	return *this;
}

Vector2D& Vector2D::operator-=(const Vector2D& a)
{
	m_x-=a.m_x;
	m_y-=a.m_y;

	return *this;
}

Vector2D& Vector2D::operator*=(const Vector2D& a)
{
	m_x*=a.m_x;
	m_y*=a.m_y;

	return *this;
}

Vector2D& Vector2D::operator/=(const Vector2D& a)
{
	m_x/=a.m_x;
	m_y/=a.m_y;

	return *this;
}

Vector2D& Vector2D::operator/=(float a)
{
	if(!a)
		a=1;

	m_x/=a;
	m_y/=a;

	return *this;
}

Vector2D& Vector2D::operator*=(float a)
{
	m_x*=a;
	m_y*=a;

	return *this;
}

std::ostream& operator<<(std::ostream& os,const Vector2D& s)
{
	return os<<"x="<<s.getX()<<" y="<<s.getY();
}

