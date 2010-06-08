#include "activetextwidget.hpp"

#include "scissor.hpp"

Sound ActiveTextWidget::m_mouse_over_sound;
Sound ActiveTextWidget::m_mouse_down_sound;

void ActiveTextWidget::setActiveFont(Font font)
{
	m_active_font=font;
}

Font& ActiveTextWidget::getActiveFont()
{
	return m_active_font;
}

void ActiveTextWidget::mouseOn()
{
	m_mouse_over_time=SDL_GetTicks();
	m_animate=true;
	m_mouse_over=true;
	
	m_mouse_over_sound.stop();
	m_mouse_over_sound.play();
}

void ActiveTextWidget::mouseOut()
{
	m_mouse_over=false;
}

void ActiveTextWidget::mouseDown(MouseEvent event)
{
	m_mouse_down_sound.stop();
	m_mouse_down_sound.play();
}

void ActiveTextWidget::draw(Graphics& graphics)
{
	glBindTexture(GL_TEXTURE_2D,0);

/*	Color(1,1,1).apply();
	
	Vector2D begin=getPosition();
	Vector2D end=getPosition()+getSize();
	
	glBegin(GL_QUADS);
		glVertex2f(begin.getX(),begin.getY());
		glVertex2f(end.getX(),begin.getY());
		glVertex2f(end.getX(),end.getY());
		glVertex2f(begin.getX(),end.getY());
	glEnd();*/
	
	float spread=float(SDL_GetTicks()-m_mouse_over_time)/100.0;
	
	if(spread>1.0)
	{
		m_animate=false;
	}
	
	Scissor scissor(graphics);
	
	if(m_animate)
	{	
		if(m_mouse_over==false)
			m_animate=false;
		
		Vector2D topposition=getPosition();
		Vector2D bottomposition=getPosition()+Vector2D(0,0.5+(spread/2.0))*getSize();
		Vector2D size=Vector2D(1,0.5-spread/2.0)*getSize();	
		
		scissor.set(topposition,size);
		
		getFont().draw(getWideText(),getPosition());
			
		scissor.set(bottomposition,size);
		
		getFont().draw(getWideText(),getPosition());		
		
		//we add some to the size so there arent any gaps between
		//the center and the other pieces		
		Vector2D centerposition=getPosition()+Vector2D(0,0.5-(spread/2.0)-0.05)*getSize();
	
		Vector2D centersize=Vector2D(1,spread+0.1)*getSize();
		
		scissor.set(centerposition,centersize);
		getActiveFont().draw(getWideText(),getPosition());
	}
	else
	{
		if(!m_mouse_over)
		{
			getFont().draw(getWideText(),getPosition());
		}
		else
		{
			getActiveFont().draw(getWideText(),getPosition());
		}
	}
}

ActiveTextWidget::ActiveTextWidget():
	m_mouse_over(false),
	m_animate(false)
{
	m_mouse_over_sound.load("data/sounds/mouseover.wav");
	m_mouse_down_sound.load("data/sounds/click.wav");
}
