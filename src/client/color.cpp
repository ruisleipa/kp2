#include "color.hpp"

#include <GL/gl.h>

Color::Color()
{
	m_red=0;
	m_green=0;
	m_blue=0;
	m_alpha=0;
}

Color::Color(float red,float green,float blue,float alpha)
{
	m_red=red;
	m_green=green;
	m_blue=blue;
	m_alpha=alpha;
}

void Color::apply()
{
	glColor4f(m_red,m_green,m_blue,m_alpha);
}

