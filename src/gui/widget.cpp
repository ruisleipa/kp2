#include "widget.hpp"

void Widget::doKeyDown(KeyEvent event)
{
	onKeyDown(event);
}

void Widget::doKeyUp(KeyEvent event)
{
	onKeyUp(event);
}

void Widget::doMouseDown(MouseEvent event)
{
	onMouseDown(event);
}

void Widget::doMouseUp(MouseEvent event)
{
	onMouseUp(event);
}

void Widget::doMouseMove(MouseEvent event)
{
	onMouseMove(event);
}

void Widget::doResize(Window& window)
{
	onResize(window);
}

void Widget::doMouseOn()
{
	onMouseOn();
}

void Widget::doMouseOut()
{
	onMouseOut();
}

void Widget::doBlur()
{
	onBlur();
}

void Widget::doFocus()
{
	onFocus();
}
	
void Widget::doDraw(Window& window)
{
	onDraw(window);
}

void Widget::doShow()
{
	onShow();
}

void Widget::doHide()
{
	onHide();
}

void Widget::onKeyDown(KeyEvent event)
{
	
}

void Widget::onKeyUp(KeyEvent event)
{

}

void Widget::onMouseDown(MouseEvent event)
{

}

void Widget::onMouseUp(MouseEvent event)
{

}

void Widget::onMouseMove(MouseEvent event)
{

}

void Widget::onResize(Window& window)
{

}

void Widget::onMouseOn()
{

}

void Widget::onMouseOut()
{

}
	
void Widget::onBlur()
{

}

void Widget::onFocus()
{

}
	
void Widget::onDraw(Window& window)
{

}

void Widget::onShow()
{

}

void Widget::onHide()
{

}

void Widget::setPosition(Vector2D position)
{
	this->position=position;
}	

Vector2D Widget::getPosition()
{
	return position;
}

Vector2D Widget::getAbsolutePosition()
{
	Vector2D position;

	if(getParent())
	{
		position+=getParent()->getAbsolutePosition();
	}
	
	return position+position;
}

void Widget::setSize(Vector2D size)
{
	this->size=size;
}	

Vector2D Widget::getSize()
{
	return size;
}

void Widget::setVisible(bool visible)
{
	this->visible=visible;
	
	if(this->visible)
		onShow();
	else
		onHide();
}	

bool Widget::getVisible()
{
	return visible;
}

Widget::Widget():
	visible(true),
	parent(0),
	window(0)
{

}

Widget::~Widget()
{

}

Container* Widget::getParent()
{
	return parent;
}

void Widget::setParent(Container* parent)
{
	this->parent=parent;
}

Window* Widget::getWindow()
{
	return window;
}

void Widget::setWindow(Window* window)
{
	this->window = window;
}
