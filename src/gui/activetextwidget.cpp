#include "activetextwidget.hpp"

#include "graphics/scissor.hpp"

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

void ActiveTextWidget::onMouseOn()
{
	m_animate=true;
	m_mouse_over=true;
	
	m_mouse_over_sound.stop();
	m_mouse_over_sound.play();	

	m_mouse_over_timer.reset();
}

void ActiveTextWidget::onMouseOut()
{
	m_mouse_over=false;
}

void ActiveTextWidget::onMouseDown(MouseEvent event)
{
	m_mouse_down_sound.stop();
	m_mouse_down_sound.play();
}

static float lerp(float a,float b,float ratio)
{
	if(ratio>1.0)
		ratio=1.0;
		
	if(ratio<0.0)
		ratio=0.0;

	return a+(b-a)*ratio;
}

void ActiveTextWidget::onDraw(Window& window)
{
	Vector2D position=getAbsolutePosition();
	
	float spread=m_mouse_over_timer.getSeconds()*10.0;
	
	Vector2D pixelsize=Vector2D(1,1)/window.getSize();
	
	if(spread>1.0)
	{
		m_animate=false;
	}
		
	position+=pixelsize;	
		
	m_border_font.draw(getWideText(),position-pixelsize*Vector2D(1,0));	
	m_border_font.draw(getWideText(),position+pixelsize*Vector2D(1,0));
	m_border_font.draw(getWideText(),position-pixelsize*Vector2D(0,1));
	m_border_font.draw(getWideText(),position+pixelsize*Vector2D(0,1));
	
	Scissor scissor(window);
	
	if(m_animate)
	{
		if(m_mouse_over==false)
			m_animate=false;
			
		Color col;
		Color acol=getFont().getColor();
		Color bcol=getActiveFont().getColor();
		
		col.setRed(lerp(acol.getRed(),bcol.getRed(),spread));
		col.setGreen(lerp(acol.getGreen(),bcol.getGreen(),spread));
		col.setBlue(lerp(acol.getBlue(),bcol.getBlue(),spread));
		col.setAlpha(lerp(acol.getAlpha(),bcol.getAlpha(),spread));

		getActiveFont().draw(getWideText(),position,col);
	}
	else
	{
		if(!m_mouse_over)
		{
			getFont().draw(getWideText(),position);
		}
		else
		{
			getActiveFont().draw(getWideText(),position);
		}
	}
}

ActiveTextWidget::ActiveTextWidget():
	m_mouse_over(false),
	m_animate(false)
{
	m_mouse_over_sound.load("data/sounds/mouseover.wav");
	m_mouse_down_sound.load("data/sounds/click.wav");
	
	m_border_font=Font("Textborder");
}

void ActiveTextWidget::autoSize()
{
	//needed for the bordered look
	//TODO: better calculation (this is an ugly hack :P)
	TextWidget::autoSize();
	setSize(getSize()+Vector2D(0.005,0));
}
