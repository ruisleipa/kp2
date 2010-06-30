#include "widget.hpp"

#include <iostream>
#include <cmath>
#include "keyevent.hpp"
#include "mouseevent.hpp"

#include "container.hpp"

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

void Widget::doResize(Graphics& graphics)
{
	onResize(graphics);
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
	
void Widget::doDraw(Graphics& graphics)
{
	onDraw(graphics);
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

void Widget::onResize(Graphics& graphics)
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
	
void Widget::onDraw(Graphics& graphics)
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

Vector2D Widget::getScreenPosition()
{
	Vector2D position;

	if(getParent())
	{
		position+=getParent()->getScreenPosition();
	}
	
	return position+m_position;
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

Widget* Widget::getRootWidget(const std::string& tag)
{
	Container* container=(Container*)getParent();
	
	if(container == 0)
	{
		std::cerr<<"Trying to get root widget \""<<tag<<"\" on a non-child widget."<<std::endl;
	}
	
	while(container->getParent())
	{
		container=(Container*)container->getParent();
	}
	
	Widget* widget=container->getWidget(tag);
	
	if(widget == 0)
	{
		std::cerr<<"Cannot find root widget \""<<tag<<"\". Will crash."<<std::endl;
	}
	
	return widget;
}

