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

void ActiveTextWidget::onMouseOn()
{
	doAnimate=true;
	mouseOverFlag=true;
	
	mouseOverSound.stop();
	mouseOverSound.play();	

	mouseOverTimer.reset();
}

void ActiveTextWidget::onMouseOut()
{
	mouseOverFlag=false;
}

void ActiveTextWidget::onMouseDown(MouseEvent event)
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

void ActiveTextWidget::onDraw(DrawEvent event)
{
	Vector2D position=event.getAreaPosition();
	
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
	
	Scissor scissor(event.getWindow());
	
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
