#include "scissor.hpp"

#include <GL/glew.h>
#include "graphics.hpp"
#include "vector2d.hpp"

void Scissor::set(Vector2D pos,Vector2D size)
{
	Vector2D displaysize=m_graphics.getDisplaySize();

	pos*=displaysize;
	size*=displaysize;
	
	glEnable(GL_SCISSOR_TEST);
	glScissor(pos.getX(),displaysize.getY()-(pos.getY()+size.getY()),size.getX(),size.getY());
}

void Scissor::reset()
{
	glDisable(GL_SCISSOR_TEST);
	set(Vector2D(0,0),m_graphics.getDisplaySize());
}

Scissor::Scissor(Graphics& graphics):
	m_graphics(graphics)
{

}

