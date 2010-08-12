#include "field.hpp"

#include "graphics/scissor.hpp"

void Field::onDraw(Window& window)
{				
	float cursorpos=getFont().getTextSize(window,getWideText().substr(0,m_cursorpos)).getX();
		
	float textoffset=-(cursorpos+0.02-getSize().getX());
	
	if(textoffset>0.001)
		textoffset=0.001;
	
	cursorpos+=getAbsolutePosition().getX()+textoffset;
	
	#if 0
	glBegin(GL_LINES);
	glVertex2d(getAbsolutePosition().getX(),getAbsolutePosition().getY()+getSize().getY()*0.8);
	glVertex2d(getAbsolutePosition().getX()+getSize().getX(),getAbsolutePosition().getY()+getSize().getY()*0.8);
	glEnd();
	#endif

	Vector2D begin=getAbsolutePosition();
	Vector2D end=begin+getSize();
	
	Scissor scissor(window);
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
		glVertex2d(cursorpos,getAbsolutePosition().getY());
		glVertex2d(cursorpos,getAbsolutePosition().getY()+getSize().getY());
		glEnd();
	}
	
	scissor.set(getAbsolutePosition(),getSize());
	//glClear(GL_COLOR_BUFFER_BIT);
	getFont().draw(window,getWideText(),getAbsolutePosition()+Vector2D(textoffset,0));
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

