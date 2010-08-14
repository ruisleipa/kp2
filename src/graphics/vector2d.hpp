#ifndef VECTOR2D_HPP
#define VECTOR2D_HPP

#include <ostream>

class Vector2D
{
	public:
		Vector2D();
		Vector2D(float x,float y);
		
		Vector2D operator+(const Vector2D& a) const;
		Vector2D operator-(const Vector2D& a) const;
		Vector2D operator*(const Vector2D& a) const;
		Vector2D operator/(const Vector2D& a) const;
		Vector2D operator*(float) const;
		Vector2D operator/(float) const;
		
		Vector2D& operator+=(const Vector2D& a);
		Vector2D& operator-=(const Vector2D& a);
		Vector2D& operator*=(const Vector2D& a);
		Vector2D& operator/=(const Vector2D& a);
		Vector2D& operator*=(float);
		Vector2D& operator/=(float);

		float getX() const	{return m_x;}
		void setX(float x)	{m_x=x;}
		float getY() const	{return m_y;}
		void setY(float y)	{m_y=y;}

		friend std::ostream& operator<<(std::ostream& os,const Vector2D& s);

	private:
		float m_x;
		float m_y;		
};

#endif // VECTOR2D_HPP
