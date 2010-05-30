#include "widget.hpp"

#include <iostream>

#include <cmath>

void Widget::keyDown(KeyEvent event)
{

}

void Widget::keyUp(KeyEvent event)
{

}

void Widget::mouseDown(MouseEvent event)
{

}

void Widget::mouseUp(MouseEvent event)
{

}

void Widget::mouseMove(MouseEvent event)
{

}

void Widget::mouseOn()
{

}

void Widget::mouseOut()
{

}

void Widget::blur()
{

}

void Widget::focus()
{

}

void Widget::draw()
{

}

void Widget::setPosition(Vector2D position)
{
	m_position=position;
}	

Vector2D Widget::getPosition()
{
	return m_position;
}

void Widget::setSize(Vector2D size)
{
	m_size=size;
}	

Vector2D Widget::getSize()
{
	return m_size;
}

Widget::Widget()
{
	m_parent=0;
}

Widget::~Widget()
{

}

View* Widget::getParent()
{
	return m_parent;
}

void Widget::setParent(View* view)
{
	m_parent=view;
}
