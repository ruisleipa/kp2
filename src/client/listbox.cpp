#include "listbox.hpp"

#include "shared/string.hpp"
#include "assert.hpp"
#include "scissor.hpp"

Texture Listbox::m_arrow_up;
Texture Listbox::m_arrow_down;
bool Listbox::m_textures_loaded=false;

void Listbox::onChange()
{
	
}

const float BAR_WIDTH=0.02;

void Listbox::onDraw(Graphics& graphics)
{
	Vector2D begin=getScreenPosition();
	Vector2D end=begin+getSize();	
	
	Scissor scissor(graphics);
	
	scissor.reset();
	
	Texture().bind();
	Color(0,0,0).apply();
	
	glBegin(GL_LINE_LOOP);
			
	glVertex2f(begin.getX(),begin.getY());
	glVertex2f(end.getX(),begin.getY());
	glVertex2f(end.getX(),end.getY());
	glVertex2f(begin.getX(),end.getY());
				
	glEnd();
	
	glBegin(GL_LINES);
			
	glVertex2f(end.getX()-BAR_WIDTH,begin.getY());
	glVertex2f(end.getX()-BAR_WIDTH,end.getY());
	
	glVertex2f(end.getX()-BAR_WIDTH,begin.getY()+BAR_WIDTH*graphics.getAspectRatio());
	glVertex2f(end.getX(),begin.getY()+BAR_WIDTH*graphics.getAspectRatio());
	
	glVertex2f(end.getX()-BAR_WIDTH,end.getY()-BAR_WIDTH*graphics.getAspectRatio());
	glVertex2f(end.getX(),end.getY()-BAR_WIDTH*graphics.getAspectRatio());
	
	glEnd();			
	
	m_arrow_up.draw(begin+Vector2D(getSize().getX()-BAR_WIDTH,0),Vector2D(BAR_WIDTH,BAR_WIDTH*graphics.getAspectRatio()));
	m_arrow_down.draw(begin+Vector2D(getSize().getX()-BAR_WIDTH,getSize().getY()-BAR_WIDTH*graphics.getAspectRatio()),Vector2D(BAR_WIDTH,BAR_WIDTH*graphics.getAspectRatio()));
	
	scissor.set(begin+Vector2D(0.001,0.001),end-Vector2D(0.001,0.001)-Vector2D(BAR_WIDTH,0));
	
	for(int i=0;i<m_items.size();++i)
	{
		if(i == m_index)
		{
			Texture().bind();
			Color(0.5,0.5,0.5,0.5).apply();
			
			Vector2D textbegin=getScreenPosition()+getFont().getTextSize(L"")*i;
			Vector2D textend=textbegin+getFont().getTextSize(L"")+getSize()*Vector2D(1,0)-Vector2D(BAR_WIDTH,0);			
						
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
	
		getFont().draw(m_items[i],getScreenPosition()+getFont().getTextSize(L"")*i);
	}	
}

void Listbox::onResize(Graphics& graphics)
{
	m_button_height=BAR_WIDTH*graphics.getAspectRatio();
}

void Listbox::onMouseDown(MouseEvent event)
{
	Vector2D inner=event.getPosition()-getScreenPosition();
	
	if(inner.getX() < getSize().getX() - BAR_WIDTH)
	{
		float y=inner.getY();
		
		setIndex(y/getFont().getTextSize(L"").getY());
	}
	else
	{
		if(inner.getY() < m_button_height)
		{
			setIndex(getIndex()-1);
		}
		
		if(inner.getY() > getSize().getY() - m_button_height)
		{
			setIndex(getIndex()+1);
		}
	}
}

void Listbox::addItem(std::string item)
{
	if(m_index == -1)
		setIndex(0);
		
	m_items.push_back(convertToWideString(item));
}

void Listbox::clearItems()
{
	m_items.clear();
	m_index=-1;
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
		
		onChange();
	}
}

Listbox::Listbox():
	m_index(-1),
	m_button_height(0)
{
	setFont(Font("Listbox"));
	//setActiveFont(Font("Listbox.active"));
	
	if(!m_textures_loaded)
	{
		m_arrow_up.load("data/images/arrowup.png");
		m_arrow_down.load("data/images/arrowdown.png");
		
		m_textures_loaded=true;
	}
}

bool Listbox::doAutoSizeOnChange()
{
	return false;
}
