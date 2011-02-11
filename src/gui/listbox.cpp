#include "listbox.hpp"

#include "utils/string.hpp"
#include "debug/assert.hpp"
#include "graphics/scissor.hpp"

#include <algorithm>
#include <cmath>

Texture Listbox::arrowUp;
Texture Listbox::arrowDown;
bool Listbox::haveTexturesBeenLoaded=false;

const float BAR_WIDTH=20;
const float BUTTON_WIDTH=BAR_WIDTH;
const float BUTTON_HEIGHT=BUTTON_WIDTH;
const float SCROLL_DEFAULT_STEP=50;
const float SCROLL_RATE=500;

static float sign(float value)
{
	if(value > 0.0)
		return 1.0;
	else if(value < 0.0)
		return -1.0;
	else
		return 0.0;
}

void Listbox::handleEvent(Event* event)
{
	if(dynamic_cast<DrawEvent*>(event))
		handleDrawEvent(dynamic_cast<DrawEvent*>(event));
	else if(dynamic_cast<MouseDownEvent*>(event))
		handleMouseDownEvent(dynamic_cast<MouseDownEvent*>(event));
}

void Listbox::handleDrawEvent(DrawEvent* event)
{
	/*
	Update the list position.
	*/	
	
	float scroll=SCROLL_RATE*scrollTimer.getSeconds()*sign(scrollPending);
	
	if(fabs(scroll) > fabs(scrollPending))
		scroll=scrollPending;
	
	scrollPending-=scroll;
	scrollOffset+=scroll;

	scrollTimer.reset();

	if(scrollOffset>0.0)
	{
		scrollOffset=0;
		scrollPending=0;
	}	
	
	float min_offset=(getFont().getTextSize(L"")*items.size()).getY();
	
	min_offset-=event->getAreaSize().getY();
	
	if(min_offset<0.0)
		min_offset=0;
	
	if(scrollOffset<-min_offset)
	{
		scrollOffset=-min_offset;
		scrollPending=0;
	}
	
	/*
	Draw
	*/
	Vector2D begin=event->getAreaPosition();
	Vector2D end=begin+event->getAreaSize();
		
	Scissor scissor(event->getWindow());
	
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
	
	scissor.set(event->getAreaPosition(),event->getAreaSize());
	
	Vector2D listbegin=Vector2D(0,scrollOffset)+event->getAreaPosition();
	
	for(int i=0;i<items.size();++i)
	{
		if(i == index)
		{
			Texture().bind();
			Color(1,1,1).apply();
			
			Vector2D textbegin=listbegin+getFont().getTextSize(L"")*i;
			
			Vector2D textend;
			textend.setY(textbegin.getY()+getFont().getTextSize(L"").getY());
			textend.setX(textbegin.getX()+event->getAreaSize().getX()-BAR_WIDTH);			

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
	
		getFont().draw(items[i].text,listbegin+getFont().getTextSize(L"")*i);
	}
	
	scissor.reset();
	
	/*
	Draw the thumb.
	*/
	float thumbLenght=event->getAreaSize().getY();
	thumbLenght /= (getFont().getTextSize(L"")*items.size()).getY();
	thumbLenght = std::min(1.0f,thumbLenght);
	thumbLenght *= event->getAreaSize().getY()-BUTTON_HEIGHT-BUTTON_HEIGHT;
	float thumbPosition=-scrollOffset;
	thumbPosition /= (getFont().getTextSize(L"")*items.size()).getY();
	thumbPosition *= event->getAreaSize().getY()-BUTTON_HEIGHT-BUTTON_HEIGHT;
	
	Texture().bind();
	Color(0,0,0,0.5).apply();
	
	glBegin(GL_QUADS);
			
	glVertex2f(end.getX()-BAR_WIDTH,begin.getY()+BUTTON_HEIGHT+thumbPosition);
	glVertex2f(end.getX(),begin.getY()+BUTTON_HEIGHT+thumbPosition);
	glVertex2f(end.getX(),begin.getY()+BUTTON_HEIGHT+thumbPosition+thumbLenght);
	glVertex2f(end.getX()-BAR_WIDTH,begin.getY()+BUTTON_HEIGHT+thumbPosition+thumbLenght);
				
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
	
	glVertex2f(end.getX()-BAR_WIDTH,begin.getY()+BAR_WIDTH);
	glVertex2f(end.getX(),begin.getY()+BAR_WIDTH);
	
	glVertex2f(end.getX()-BAR_WIDTH,end.getY()-BAR_WIDTH);
	glVertex2f(end.getX(),end.getY()-BAR_WIDTH);
	
	glEnd();			
	
	arrowUp.draw(Vector2D(end.getX()-BAR_WIDTH,begin.getY()),Vector2D(BAR_WIDTH,BAR_WIDTH));
	arrowDown.draw(Vector2D(end.getX()-BAR_WIDTH,end.getY()-BAR_WIDTH),Vector2D(BAR_WIDTH,BAR_WIDTH));	
}

void Listbox::onResize(Window& window)
{

}

void Listbox::handleMouseDownEvent(MouseDownEvent* event)
{		
	if(event->isButtonDown(MouseEvent::WHEELUP))
	{
		if(scrollPending<0)
			scrollPending=0;
		
		scrollPending+=SCROLL_DEFAULT_STEP;

		return;
	}

	if(event->isButtonDown(MouseEvent::WHEELDOWN))
	{
		if(scrollPending>0)
			scrollPending=0;
	
		scrollPending-=SCROLL_DEFAULT_STEP;

		return;
	}
	
	Vector2D inner=event->getMousePosition();

	if(inner.getX() < event->getAreaSize().getX() - BAR_WIDTH)
	{
		float y=inner.getY()-scrollOffset;
		
		setIndex(y/getFont().getTextSize(L"").getY());
	}
	else
	{	
		if(event->isButtonDown(MouseEvent::LEFT) || event->isButtonDown(MouseEvent::RIGHT))
		{		
			if(inner.getY() < BUTTON_HEIGHT)
			{
				scrollPending=SCROLL_DEFAULT_STEP;
				scrollTimer.reset();
			}
			
			if(inner.getY() > event->getAreaSize().getY() - BUTTON_HEIGHT)
			{
				scrollPending=-SCROLL_DEFAULT_STEP;
				scrollTimer.reset();
			}
		}
		
		
	}
}

void Listbox::setChangeHandler(std::tr1::function<void()> handler)
{
	changeHandler=handler;
}

void Listbox::addItem(std::string item,int tag)
{
	if(index == -1)
		setIndex(0);
		
	Item newitem;
	newitem.text=convertToWideString(item);
	newitem.tag=tag;
		
	items.push_back(newitem);
}

void Listbox::clearItems()
{
	items.clear();
	index=-1;
}

int Listbox::getCurrentItemTag()
{
	if(index == -1)
		return -1;
		
	return items[index].tag;
}

std::string Listbox::getCurrentItemString()
{
	if(index == -1)
		return "";
		
	return convertToString(items[index].text);
}

int Listbox::getIndex()
{
	return index;
}

void Listbox::setIndex(int newIndex)
{
	if(newIndex >= 0 && newIndex < items.size())
	{
		index=newIndex;
		
		if(changeHandler)
			changeHandler();
	}
}

Listbox::Listbox():
	index(-1),
	scrollOffset(0.0),
	scrollPending(0)
{
	setFont(Font("Listbox"));
	//setActiveFont(Font("Listbox.active"));
	
	if(!haveTexturesBeenLoaded)
	{
		arrowUp=Texture("data/images/arrowup.png");
		arrowDown=Texture("data/images/arrowdown.png");
		
		haveTexturesBeenLoaded=true;
	}
}

bool Listbox::doAutoSizeOnChange()
{
	return false;
}
