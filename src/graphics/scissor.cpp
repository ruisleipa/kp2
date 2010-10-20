#include "scissor.hpp"

#include <GL/glew.h>
#include "window.hpp"
#include "vector2d.hpp"

void Scissor::set(Vector2D pos,Vector2D size)
{
	Vector2D windowsize=window.getSize();

	glEnable(GL_SCISSOR_TEST);
	glScissor(pos.getX(),windowsize.getY()-(pos.getY()+size.getY()),size.getX(),size.getY());
}

void Scissor::reset()
{
	glDisable(GL_SCISSOR_TEST);
	set(Vector2D(0,0),window.getSize());
}

Scissor::Scissor(Window& window):
	window(window)
{

}

