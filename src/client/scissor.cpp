#include "scissor.hpp"

#include <GL/glew.h>
#include <algorithm>

#include "graphics.hpp"

void Scissor::set(Vector2D pos,Vector2D size)
{
	Vector2D displaysize=Graphics::getInstance().getDisplaySize();

	pos*=displaysize;
	size*=displaysize;
	
	glEnable(GL_SCISSOR_TEST);
	glScissor(pos.getX(),displaysize.getY()-(pos.getY()+size.getY()),size.getX(),size.getY());
}
/*
void Scissor::setClipped(Vector2D pos,Vector2D size,Vector2D* cpos,Vector2D* csize)
{
	// This function sets the scissor box so that the new scissor box is clipped
	// with the old one.

	Vector2D displaysize=Graphics::getInstance().getDisplaySize();

	GLint box[4];

	glGetIntegerv(GL_SCISSOR_BOX,box);

	Vector2D oldbegin = Vector2D(box[0],displaysize.getY()-box[1]-box[3]);
	Vector2D oldend = oldbegin+Vector2D(box[2],box[3]);

	Vector2D newbegin;
	Vector2D newend;
	Vector2D end = pos + size;

	newbegin.setX(std::max(pos.getX(),oldbegin.getX()));
	newbegin.setY(std::max(pos.getY(),oldbegin.getY()));
	newend.setX(std::min(end.getX(),oldend.getX()));
	newend.setY(std::min(end.getY(),oldend.getY()));

	Vector2D newsize=newend-newbegin;

	if(newsize.getY()<0)
		newsize.setY(0);

	if(newsize.getX()<0)
		newsize.setX(0);

	Scissor::set(newbegin,newsize);

	if(cpos)
		*cpos=newbegin;
	if(csize)
		*csize=newsize;

	return;
}

void Scissor::get(Vector2D& pos,Vector2D& size)
{
	Vector2D displaysize=Graphics::getInstance().getDisplaySize();

	GLint box[4];

	glGetIntegerv(GL_SCISSOR_BOX,box);

	pos=Vector2D(box[0],displaysize.getY()-box[1]-box[3]);
	size=Vector2D(box[2],box[3]);
}*/

void Scissor::reset()
{
	glDisable(GL_SCISSOR_TEST);
	Scissor::set(Vector2D(0,0),Graphics::getInstance().getDisplaySize());
}

