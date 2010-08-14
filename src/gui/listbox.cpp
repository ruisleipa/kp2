#include "listbox.hpp"

#include "utils/string.hpp"
#include "debug/assert.hpp"
#include "graphics/scissor.hpp"

#include <algorithm>
#include <cmath>

Texture Listbox::m_arrow_up;
Texture Listbox::m_arrow_down;
bool Listbox::m_textures_loaded=false;

const float BAR_WIDTH=0.02;
const float SCROLL_DEFAULT_STEP=0.4;
const float SCROLL_RATE=1;

static float sign(float value)
{
	if(value > 0.0)
		return 1.0;
	else if(value < 0.0)
		return -1.0;
	else
		return 0.0;
}

void Listbox::onDraw(Window& window)
{
	/*
	Update the list position.
	*/	
	
	float scroll=SCROLL_RATE*m_scroll_timer.getSeconds()*sign(m_scroll_pending);
	
	if(fabs(scroll) > fabs(m_scroll_pending))
		scroll=m_scroll_pending;
	
	m_scroll_pending-=scroll;
	m_scroll_offset+=scroll;

	m_scroll_timer.reset();

	if(m_scroll_offset>0.0)
	{
		m_scroll_offset=0;
		m_scroll_pending=0;
	}	
	
	float min_offset=(getFont().getTextSize(window,L"")*m_items.size()).getY();
	
	min_offset-=getSize().getY();
	
	if(min_offset<0.0)
		min_offset=0;
	
	if(m_scroll_offset<-min_offset)
	{
		m_scroll_offset=-min_offset;
		m_scroll_pending=0;
	}
	
	/*
	Draw
	*/
	Vector2D begin=getAbsolutePosition();
	Vector2D end=begin+getSize();
		
	Scissor scissor(window);
	
	/*
	Draw list.
	*/
	Texture().bind();
	Color(1,1,1,0.2).apply();
	
	glBegin(GL_QUADS);
			
	glVertex2f(begin.getX(),begin.getY());
	glVertex2f(end.getX()-BAR_WIDTH,begin.getY());
	glVertex2f(end.getX()-BAR_WIDTH,end.getY());
	glVertex2f(begin.getX(),end.getY());
				
	glEnd();	
	
	scissor.set(begin+Vector2D(0.001,0.001),getSize()-Vector2D(0.001,0.001)-Vector2D(BAR_WIDTH,0));
	
	Vector2D listbegin=Vector2D(0,m_scroll_offset)+getAbsolutePosition();
	
	for(int i=0;i<m_items.size();++i)
	{
		if(i == m_index)
		{
			Texture().bind();
			Color(1,1,1).apply();
			
			Vector2D textbegin=listbegin+getFont().getTextSize(window,L"")*i;
			Vector2D textend=textbegin+getFont().getTextSize(window,L"")+getSize()*Vector2D(1,0)-Vector2D(BAR_WIDTH,0);			
						
			glBegin(GL_QUADS);
			
			glVertex2f(textbegin.getX(),textbegin.getY());
			glVertex2f(textend.getX(),textbegin.getY());
			glVertex2f(textend.getX(),textend.getY());
			glVertex2f(textbegin.getX(),textend.getY());
						
			glEnd();
		}
		else
		{
			Color(1,1,1).apply();
		}		
	
		getFont().draw(window,m_items[i].m_string,listbegin+getFont().getTextSize(window,L"")*i);
	}
	
	scissor.reset();
	
	/*
	Draw the thumb.
	*/
	float thumb_lenght=getSize().getY();
	thumb_lenght /= (getFont().getTextSize(window,L"")*m_items.size()).getY();
	thumb_lenght = std::min(1.0f,thumb_lenght);
	thumb_lenght *= getSize().getY()-m_button_height-m_button_height;
	float thumb_pos=-m_scroll_offset;
	thumb_pos /= (getFont().getTextSize(window,L"")*m_items.size()).getY();
	thumb_pos *= getSize().getY()-m_button_height-m_button_height;
	
	Texture().bind();
	Color(1,1,1,0.5).apply();
	
	glBegin(GL_QUADS);
			
	glVertex2f(end.getX()-BAR_WIDTH,begin.getY()+m_button_height+thumb_pos);
	glVertex2f(end.getX(),begin.getY()+m_button_height+thumb_pos);
	glVertex2f(end.getX(),begin.getY()+m_button_height+thumb_pos+thumb_lenght);
	glVertex2f(end.getX()-BAR_WIDTH,begin.getY()+m_button_height+thumb_pos+thumb_lenght);
				
	glEnd();
	
	/*
	Draw borders.
	*/
	Texture().bind();
	Color(0,0,0).apply();
	
	glBegin(GL_LINE_LOOP);
			
	glVertex2f(begin.getX(),begin.getY());
	glVertex2f(end.getX(),begin.getY());
	glVertex2f(end.getX(),end.getY());
	glVertex2f(begin.getX(),end.getY());
				
	glEnd();
	
	/*
	Draw scroll bar.
	*/
	glBegin(GL_LINES);
			
	glVertex2f(end.getX()-BAR_WIDTH,begin.getY());
	glVertex2f(end.getX()-BAR_WIDTH,end.getY());
	
	glVertex2f(end.getX()-BAR_WIDTH,begin.getY()+m_button_height);
	glVertex2f(end.getX(),begin.getY()+m_button_height);
	
	glVertex2f(end.getX()-BAR_WIDTH,end.getY()-m_button_height);
	glVertex2f(end.getX(),end.getY()-m_button_height);
	
	glEnd();			
	
	m_arrow_up.draw(Vector2D(end.getX()-BAR_WIDTH,begin.getY()),Vector2D(BAR_WIDTH,m_button_height));
	m_arrow_down.draw(Vector2D(end.getX()-BAR_WIDTH,end.getY()-m_button_height),Vector2D(BAR_WIDTH,m_button_height));	
}

void Listbox::onResize(Window& window)
{
	m_button_height=BAR_WIDTH*window.getAspectRatio();
}

void Listbox::onMouseDown(MouseEvent event)
{		
	if(event.isButtonDown(MouseEvent::WHEELUP))
	{
		if(m_scroll_pending<0)
			m_scroll_pending=0;
		
		m_scroll_pending+=SCROLL_DEFAULT_STEP;

		return;
	}

	if(event.isButtonDown(MouseEvent::WHEELDOWN))
	{
		if(m_scroll_pending>0)
			m_scroll_pending=0;
	
		m_scroll_pending-=SCROLL_DEFAULT_STEP;

		return;
	}
	
	Vector2D inner=event.getPosition()-getAbsolutePosition();
	
	if(inner.getX() < getSize().getX() - BAR_WIDTH)
	{
		float y=inner.getY()-m_scroll_offset;
		
		setIndex(y/getFont().getTextSize(event.getWindow(),L"").getY());
	}
	else
	{	
		if(event.isButtonDown(MouseEvent::LEFT) || event.isButtonDown(MouseEvent::RIGHT))
		{		
			if(inner.getY() < m_button_height)
			{
				m_scroll_pending=SCROLL_DEFAULT_STEP;
				m_scroll_timer.reset();
			}
			
			if(inner.getY() > getSize().getY() - m_button_height)
			{
				m_scroll_pending=-SCROLL_DEFAULT_STEP;
				m_scroll_timer.reset();
			}
		}
		
		
	}
}

void Listbox::onMouseUp(MouseEvent event)
{
	//m_scroll_pending=0;
}

void Listbox::onMouseOut()
{
	//m_scroll_pending=0;
}

void Listbox::setChangeHandler(Callback0 handler)
{
	m_change_handler=handler;
}

void Listbox::addItem(std::string item,int tag)
{
	if(m_index == -1)
		setIndex(0);
		
	Item newitem;
	newitem.m_string=convertToWideString(item);
	newitem.m_tag=tag;
		
	m_items.push_back(newitem);
}

void Listbox::clearItems()
{
	m_items.clear();
	m_index=-1;
}

int Listbox::getCurrentItemTag()
{
	if(m_index == -1)
		return 0;
		
	return m_items[m_index].m_tag;
}

std::string Listbox::getCurrentItemString()
{
	if(m_index == -1)
		return "";
		
	return convertToString(m_items[m_index].m_string);
}

int Listbox::getIndex()
{
	return m_index;
}

void Listbox::setIndex(int index)
{
	if(index >= 0 && index < m_items.size())
	{
		m_index=index;
		
		m_change_handler();
	}
}

Listbox::Listbox():
	m_index(-1),
	m_scroll_offset(0.0),
	m_scroll_pending(0),
	m_button_height(0)
{
	setFont(Font("Listbox"));
	//setActiveFont(Font("Listbox.active"));
	
	if(!m_textures_loaded)
	{
		m_arrow_up=Texture("data/images/arrowup.png");
		m_arrow_down=Texture("data/images/arrowdown.png");
		
		m_textures_loaded=true;
	}
}

bool Listbox::doAutoSizeOnChange()
{
	return false;
}
