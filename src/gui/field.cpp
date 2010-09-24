#include "field.hpp"

#include "graphics/scissor.hpp"

void Field::onDraw(DrawEvent event)
{
	float cursorpos=getFont().getTextSize(getWideText().substr(0,m_cursorpos)).getX();
		
	float textoffset=-(cursorpos+0.02-event.getAreaSize().getX());
	
	if(textoffset>0.001)
		textoffset=0.001;
	
	cursorpos+=event.getAreaPosition().getX()+textoffset;

	Vector2D begin=event.getAreaPosition();
	Vector2D end=begin+event.getAreaSize();
	
	Scissor scissor(event.getWindow());
	scissor.reset();	
	
	Color(0,0,0).apply();
	Texture().bind();
	
	glBegin(GL_LINE_LOOP);
	glVertex2d(begin.getX(),begin.getY());
	glVertex2d(end.getX(),begin.getY());
	glVertex2d(end.getX(),end.getY());
	glVertex2d(begin.getX(),end.getY());
	glEnd();
	
	if(m_focused && int(m_blink_timer.getSeconds()/0.750)%2)
	{
		glBegin(GL_LINES);
		glVertex2d(cursorpos,event.getAreaPosition().getY());
		glVertex2d(cursorpos,event.getAreaPosition().getY()+event.getAreaSize().getY());
		glEnd();
	}
	
	scissor.set(event.getAreaPosition(),event.getAreaSize());
	//glClear(GL_COLOR_BUFFER_BIT);
	getFont().draw(getWideText(),event.getAreaPosition()+Vector2D(textoffset,0));
}

void Field::onKeyDown(KeyEvent event)
{
	std::wstring text=getWideText();

	switch(event.getKey())
	{
		case SDLK_BACKSPACE:
			if(m_cursorpos)
			{
				text.erase(m_cursorpos-1,1);
				m_cursorpos--;
				setText(text);
			}
			break;
			
		case SDLK_END:
			m_cursorpos=text.length();
			break;
			
		case SDLK_HOME:
			m_cursorpos=0;
			break;
			
		case SDLK_LEFT:
			m_cursorpos--;
			if(m_cursorpos<0)
			{
				m_cursorpos=0;
			}
			break;
			
		case SDLK_RIGHT:
			m_cursorpos++;
			if(m_cursorpos>text.length())
			{
				m_cursorpos=text.length();
			}
			break;

		case SDLK_DELETE:
			if(m_cursorpos<=text.length())
			{
				text.erase(m_cursorpos,1);
				setText(text);
			}
			break;
					
		default:
		
			if(event.getUnicode()>=0x20)
			{
				text.insert(m_cursorpos++,1,wchar_t(event.getUnicode()));
				setText(text);
			}
			break;
	}
}

void Field::onFocus()
{
	m_focused=true;
	
	m_blink_timer.reset();
}

void Field::onBlur()
{
	m_focused=false;
}

Field::Field():
	m_cursorpos(0),
	m_focused(false)
{
	setFont(Font("Field"));
}

bool Field::doAutoSizeOnChange()
{
	return false;
}

