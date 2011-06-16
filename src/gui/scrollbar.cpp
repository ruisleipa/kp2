#include "scrollbar.hpp"

#include "graphics/scissor.hpp"

Texture ScrollBar::arrowUp;
Texture ScrollBar::arrowDown;
bool ScrollBar::haveTexturesBeenLoaded=false;

void ScrollBar::setRange(int min, int max)
{
	this->min = min;
	this->max = max;
	
	int range = max - min + 1;
	
	if(thumbSize > range)
	{
		thumbSize = range;
		value = 0;
	}
	
	if(value + thumbSize - 1 > max)
	{
		value -= value + thumbSize - 1 - max;
	}
}

void ScrollBar::setThumbSize(int size)
{
	int range = max - min + 1;
	
	thumbSize = size;
	
	if(thumbSize > range)
	{
		thumbSize = range;
		value = 0;
	}
	
	if(value + thumbSize - 1 > max)
	{
		value -= value + thumbSize - 1 - max;
	}
}

int ScrollBar::getValue()
{
	return value;
}

void ScrollBar::handleEvent(Event* event)
{
	if(dynamic_cast<DrawEvent*>(event))
		handleDrawEvent(dynamic_cast<DrawEvent*>(event));
	else if(dynamic_cast<MouseDownEvent*>(event))
		handleMouseDownEvent(dynamic_cast<MouseDownEvent*>(event));
		
	Widget::handleEvent(event);
}

void ScrollBar::handleDrawEvent(DrawEvent* event)
{
	std::stringstream ss;
	
	ss << "min = " << min << "\n";
	ss << "max = " << max << "\n";
	ss << "value = " << value << "\n";
	ss << "thumbSize = " << thumbSize << "\n";
	ss << "range = " << value << " - " << value + thumbSize - 1;

	setToolTip(ss.str());

	Vector2D position = event->getAreaPosition();
	
	glPushMatrix();
	glTranslatef(position.getX(), position.getY(), 0);
	
	int shortAxis = getShortAxis(event->getAreaSize());
	int longAxis = getLongAxis(event->getAreaSize());
	
	Color(1, 1, 1).apply();
	
	Vector2D buttonSize = Vector2D(shortAxis, shortAxis);
	
	Vector2D upButtonPosition = convertToReal(0, 0);
	
	arrowUp.draw(upButtonPosition, buttonSize);
	
	Vector2D downButtonPosition = convertToReal(0, longAxis - shortAxis);
	
	arrowDown.draw(downButtonPosition, buttonSize);
	
	{
		int range = max - min + 1;
		int thumbSize = float(this->thumbSize) / float(range) * float(longAxis - shortAxis * 2);
		int thumbPosition = shortAxis + float(value) / float(range) * float(longAxis - shortAxis * 2);
		
		Vector2D begin = convertToReal(0, thumbPosition);
		Vector2D end = convertToReal(shortAxis, thumbPosition + thumbSize);
		
		Texture().bind();
		Color(0, 0, 0).apply();
		
		glBegin(GL_QUADS);
		
		glVertex2f(begin.getX(), begin.getY());
		glVertex2f(end.getX(), begin.getY());
		glVertex2f(end.getX(), end.getY());
		glVertex2f(begin.getX(), end.getY());
		
		glEnd();
	}
	
	/*
	Draw borders.
	*/
	{
		Vector2D begin(0, 0);
		Vector2D end = event->getAreaSize();
	
		Scissor scissor(event->getWindow(), Vector2D(0, 0), event->getWindow().getSize());
	
		Texture().bind();
		Color(0,0,0).apply();
		
		glBegin(GL_LINE_LOOP);
		
		glVertex2f(begin.getX(), begin.getY());
		glVertex2f(end.getX(), begin.getY());
		glVertex2f(end.getX(), end.getY());
		glVertex2f(begin.getX(), end.getY());
		
		glEnd();
		
		Vector2D upBegin = convertToReal(0, shortAxis);
		Vector2D upEnd = convertToReal(shortAxis, shortAxis);
		Vector2D downBegin = convertToReal(0, longAxis - shortAxis);
		Vector2D downEnd = convertToReal(shortAxis, longAxis - shortAxis);
		
		glBegin(GL_LINES);
		
		glVertex2f(upBegin.getX(), upBegin.getY());
		glVertex2f(upEnd.getX(), upEnd.getY());
		glVertex2f(downBegin.getX(), downBegin.getY());
		glVertex2f(downEnd.getX(), downEnd.getY());
		
		glEnd();
	}
	
	glPopMatrix();
}

void ScrollBar::handleMouseDownEvent(MouseDownEvent* event)
{		
	if(event->isButtonDown(MouseEvent::WHEELUP))
		tickDown();

	if(event->isButtonDown(MouseEvent::WHEELDOWN))
		tickUp();
	
	if(event->isButtonDown(MouseEvent::LEFT))
	{
		int mousePosition = getLongAxis(event->getMousePosition());
		int buttonSize = getShortAxis(event->getAreaSize());
		int size = getLongAxis(event->getAreaSize());
		
		if(mousePosition <= buttonSize)
			tickDown();
		
		if(mousePosition >= size - buttonSize)
			tickUp();
	}
}

void ScrollBar::tickDown()
{
	int tick = thumbSize / 10;

	value -= tick;
	
	if(value < min)
		value = min;
}

void ScrollBar::tickUp()
{
	int tick = thumbSize / 10;

	value += tick;
	
	if(value > (max - thumbSize) + 1)
		value = (max - thumbSize) + 1;
}

void ScrollBar::setChangeHandler(std::tr1::function<void(int)> handler)
{
	changeHandler = handler;
}

ScrollBar::ScrollBar():
	min(0),
	max(9),
	value(0),
	thumbSize(1)
{
	if(!haveTexturesBeenLoaded)
	{
		arrowUp=Texture("data/images/arrowup.png");
		arrowDown=Texture("data/images/arrowdown.png");
		
		haveTexturesBeenLoaded=true;
	}
}
