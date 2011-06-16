#include "scissor.hpp"

#include "window.hpp"
#include "vector2d.hpp"

#include <iostream>

Scissor::Scissor(Window& window, Vector2D position, Vector2D size):
	window(window)
{
	glGetBooleanv(GL_SCISSOR_TEST, &wasScissorEnabled);
	glGetIntegerv(GL_SCISSOR_BOX, scissorBox);
	
	Vector2D currentPosition(scissorBox[0], scissorBox[1]);
	Vector2D currentSize(scissorBox[2], scissorBox[3]);
	
	convertFromOpenGl(currentPosition, currentSize);
	
	Vector2D currentEnd = currentPosition + currentSize;
	Vector2D end = position + size;
	
	Vector2D newPosition;
	
	newPosition.setX(std::max(currentPosition.getX(), position.getX()));
	newPosition.setY(std::max(currentPosition.getY(), position.getY()));
	
	Vector2D newEnd;
	
	newEnd.setX(std::min(currentEnd.getX(), end.getX()));
	newEnd.setY(std::min(currentEnd.getY(), end.getY()));
	
	Vector2D newSize = newEnd - newPosition;
	
	convertToOpenGl(newPosition, newSize);
	
	glEnable(GL_SCISSOR_TEST);
	glScissor(newPosition.getX() + 0.5, newPosition.getY() + 0.5, newSize.getX() + 0.5, newSize.getY() + 0.5);
	/*
	convertToOpenGl(position, size);
	
	glEnable(GL_SCISSOR_TEST);
	glScissor(position.getX(), position.getY(), size.getX(), size.getY());
	*/
}

Scissor::~Scissor()
{
	if(wasScissorEnabled == false)
	{
		glDisable(GL_SCISSOR_TEST);
		
		Vector2D windowsize = window.getSize();
		
		glScissor(0, 0, windowsize.getX(), windowsize.getY());
	}
	else
	{
		glScissor(scissorBox[0], scissorBox[1], scissorBox[2], scissorBox[3]);
	}
}

void Scissor::convertFromOpenGl(Vector2D& position, Vector2D& size)
{
	int y = window.getSize().getY() - position.getY() - size.getY();
	
	position.setY(y);
}

void Scissor::convertToOpenGl(Vector2D& position, Vector2D& size)
{
	int y = window.getSize().getY() - position.getY() - size.getY();
	
	position.setY(y);
}
