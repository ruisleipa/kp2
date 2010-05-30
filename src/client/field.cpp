#include "field.hpp"

#include "ui.hpp"
#include "scissor.hpp"

void Field::draw()
{
	if(!getFont())
		return;	
				
	float cursorpos=getFont()->getTextSize(getWideText().substr(0,m_cursorpos)).getX();
		
	float textoffset=-(cursorpos+0.02-getSize().getX());
	
	if(textoffset>0.001)
		textoffset=0.001;
	
	cursorpos+=getPosition().getX()+textoffset;
	
	#if 0
	glBegin(GL_LINES);
	glVertex2d(getPosition().getX(),getPosition().getY()+getSize().getY()*0.8);
	glVertex2d(getPosition().getX()+getSize().getX(),getPosition().getY()+getSize().getY()*0.8);
	glEnd();
	#endif

	Vector2D begin=getPosition();
	Vector2D end=begin+getSize();
	
	Scissor::reset();
	
	Color(0,0,0).apply();
	glBindTexture(GL_TEXTURE_2D,0);
	
	glBegin(GL_LINE_LOOP);
	glVertex2d(begin.getX(),begin.getY());
	glVertex2d(end.getX(),begin.getY());
	glVertex2d(end.getX(),end.getY());
	glVertex2d(begin.getX(),end.getY());
	glEnd();
	
	if(m_focused && (SDL_GetTicks()/750)%2)
	{
		glBegin(GL_LINES);
		glVertex2d(cursorpos,getPosition().getY());
		glVertex2d(cursorpos,getPosition().getY()+getSize().getY());
		glEnd();
	}
	
	Scissor::set(getPosition(),getSize());
	
	getFont()->draw(getWideText(),getPosition()+Vector2D(textoffset,0));
}

void Field::keyDown(KeyEvent event)
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

void Field::focus()
{
	m_focused=true;
}

void Field::blur()
{
	m_focused=false;
}

Field::Field()
{
	m_cursorpos=0;
	m_focused=false;
	
	setFont(Ui::getInstance().getFont("Field"));
}

bool Field::doAutoSizeOnChange()
{
	return false;
}

