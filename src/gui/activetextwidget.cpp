#include "activetextwidget.hpp"

#include "graphics/scissor.hpp"

Sound ActiveTextWidget::mouseOverSound;
Sound ActiveTextWidget::mouseDownSound;

void ActiveTextWidget::setActiveFont(Font font)
{
	activeFont=font;
}

Font& ActiveTextWidget::getActiveFont()
{
	return activeFont;
}

void ActiveTextWidget::handleMouseOverEvent(MouseOverEvent* event)
{
	doAnimate=true;
	mouseOverFlag=true;
	
	mouseOverSound.stop();
	mouseOverSound.play();	

	mouseOverTimer.reset();
}

void ActiveTextWidget::handleMouseOutEvent(MouseOutEvent* event)
{
	mouseOverFlag=false;
}

void ActiveTextWidget::handleMouseDownEvent(MouseDownEvent* event)
{
	mouseDownSound.stop();
	mouseDownSound.play();
}

static float lerp(float a,float b,float ratio)
{
	if(ratio>1.0)
		ratio=1.0;
		
	if(ratio<0.0)
		ratio=0.0;

	return a+(b-a)*ratio;
}

void ActiveTextWidget::handleEvent(Event* event)
{
	if(dynamic_cast<DrawEvent*>(event))
		handleDrawEvent(dynamic_cast<DrawEvent*>(event));
	else if(dynamic_cast<MouseOverEvent*>(event))
		handleMouseOverEvent(dynamic_cast<MouseOverEvent*>(event));
	else if(dynamic_cast<MouseOutEvent*>(event))
		handleMouseOutEvent(dynamic_cast<MouseOutEvent*>(event));
	else if(dynamic_cast<MouseDownEvent*>(event))
		handleMouseDownEvent(dynamic_cast<MouseDownEvent*>(event));
}

void ActiveTextWidget::handleDrawEvent(DrawEvent* event)
{
	std::cout<<event->getAreaPosition()<<std::endl;

	Vector2D position=event->getAreaPosition();
	
	float spread=mouseOverTimer.getSeconds()*10.0;
	
	Vector2D pixelsize=Vector2D(1,1);
	
	if(spread>1.0)
	{
		doAnimate=false;
	}
		
	position+=pixelsize;	
		
	borderFont.draw(getWideText(),position-pixelsize*Vector2D(1,0));	
	borderFont.draw(getWideText(),position+pixelsize*Vector2D(1,0));
	borderFont.draw(getWideText(),position-pixelsize*Vector2D(0,1));
	borderFont.draw(getWideText(),position+pixelsize*Vector2D(0,1));
	
	Scissor scissor(event->getWindow());
	
	if(doAnimate)
	{
		if(mouseOverFlag==false)
			doAnimate=false;
			
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
		if(!mouseOverFlag)
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
	mouseOverFlag(false),
	doAnimate(false)
{
	mouseOverSound.load("data/sounds/mouseover.wav");
	mouseDownSound.load("data/sounds/click.wav");
	
	borderFont=Font("Textborder");
}

void ActiveTextWidget::autoSize()
{
	//needed for the bordered look
	//TODO: better calculation (this is an ugly hack :P)
	TextWidget::autoSize();
	setPixelSize(getSize()+Vector2D(2,2));
}
