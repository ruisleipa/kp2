#include "field.hpp"

#include "graphics/scissor.hpp"

void Field::handleEvent(Event* event)
{
	if(dynamic_cast<DrawEvent*>(event))
		handleDrawEvent(dynamic_cast<DrawEvent*>(event));
	else if(dynamic_cast<KeyDownEvent*>(event))
		handleKeyDownEvent(dynamic_cast<KeyDownEvent*>(event));
	else if(dynamic_cast<FocusEvent*>(event))
		handleFocusEvent();
	else if(dynamic_cast<BlurEvent*>(event))
		handleBlurEvent();
}

void Field::handleDrawEvent(DrawEvent* event)
{
	float cursorpos=getFont().getTextSize(getWideText().substr(0,cursorPosition)).getX();
		
	float textoffset=-(cursorpos+0.02-event->getAreaSize().getX());
	
	if(textoffset>0.001)
		textoffset=0.001;
	
	cursorpos+=event->getAreaPosition().getX()+textoffset;

	Vector2D begin=event->getAreaPosition();
	Vector2D end=begin+event->getAreaSize();
	
	Scissor scissor(event->getWindow());
	scissor.reset();	
	
	Color(0,0,0).apply();
	Texture().bind();
	
	glBegin(GL_LINE_LOOP);
	glVertex2d(begin.getX(),begin.getY());
	glVertex2d(end.getX(),begin.getY());
	glVertex2d(end.getX(),end.getY());
	glVertex2d(begin.getX(),end.getY());
	glEnd();
	
	if(isFocused && int(blinkTimer.getSeconds()/0.750)%2)
	{
		glBegin(GL_LINES);
		glVertex2d(cursorpos,event->getAreaPosition().getY());
		glVertex2d(cursorpos,event->getAreaPosition().getY()+event->getAreaSize().getY());
		glEnd();
	}
	
	scissor.set(event->getAreaPosition(),event->getAreaSize());
	//glClear(GL_COLOR_BUFFER_BIT);
	getFont().draw(getWideText(),event->getAreaPosition()+Vector2D(textoffset,0));
}

void Field::handleKeyDownEvent(KeyDownEvent* event)
{
	std::wstring text=getWideText();

	switch(event->getKey())
	{
		case SDLK_BACKSPACE:
			if(cursorPosition)
			{
				text.erase(cursorPosition-1,1);
				cursorPosition--;
				setText(text);
			}
			break;
			
		case SDLK_END:
			cursorPosition=text.length();
			break;
			
		case SDLK_HOME:
			cursorPosition=0;
			break;
			
		case SDLK_LEFT:
			cursorPosition--;
			if(cursorPosition<0)
			{
				cursorPosition=0;
			}
			break;
			
		case SDLK_RIGHT:
			cursorPosition++;
			if(cursorPosition>text.length())
			{
				cursorPosition=text.length();
			}
			break;

		case SDLK_DELETE:
			if(cursorPosition<=text.length())
			{
				text.erase(cursorPosition,1);
				setText(text);
			}
			break;
					
		default:
		
			if(event->getUnicode()>=0x20)
			{
				text.insert(cursorPosition++,1,wchar_t(event->getUnicode()));
				setText(text);
			}
			break;
	}
}

void Field::handleFocusEvent()
{
	isFocused=true;
	
	blinkTimer.reset();
}

void Field::handleBlurEvent()
{
	isFocused=false;
}

Field::Field():
	cursorPosition(0),
	isFocused(false)
{
	setFont(Font("Field"));
}

bool Field::doAutoSizeOnChange()
{
	return false;
}

