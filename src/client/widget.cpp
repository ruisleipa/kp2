#include "widget.hpp"

#include <iostream>
#include <cmath>
#include "keyevent.hpp"
#include "mouseevent.hpp"

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

void Widget::draw(Graphics& graphics)
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

void Widget::setVisible(bool visible)
{
	m_visible=visible;
	
	if(visible)
		onShow();
	else
		onHide();
}	

bool Widget::getVisible()
{
	return m_visible;
}

Widget::Widget():
	m_parent(0),
	m_visible(true)
{

}

Widget::~Widget()
{

}

Widget* Widget::getParent()
{
	return m_parent;
}

void Widget::setParent(Widget* view)
{
	m_parent=view;
}

