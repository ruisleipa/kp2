#include "widget.hpp"

void Widget::keyDown(KeyEvent event)
{
	onKeyDown(event);
}

void Widget::keyUp(KeyEvent event)
{
	onKeyUp(event);
}

void Widget::mouseDown(MouseEvent event)
{
	onMouseDown(event);
}

void Widget::mouseUp(MouseEvent event)
{
	onMouseUp(event);
}

void Widget::mouseMove(MouseEvent event)
{
	onMouseMove(event);
}

void Widget::resize(Window& window)
{
	onResize(window);
}

void Widget::mouseOn()
{
	onMouseOn();
}

void Widget::mouseOut()
{
	onMouseOut();
}

void Widget::blur()
{
	onBlur();
}

void Widget::focus()
{
	onFocus();
}
	
void Widget::draw(Window& window)
{
	onDraw(window);
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
	Vector2D absolutePosition;

	if(getParent())
	{
		absolutePosition+=getParent()->getAbsolutePosition();
	}
	
	return absolutePosition+position;
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
	parent(0)
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
