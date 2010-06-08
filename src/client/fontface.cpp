#include "fontface.hpp"

#include "graphics.hpp"

FontFace::FontFace(Graphics& graphics):
	m_graphics(graphics),
	m_height(0),
	m_font(0)
{

}

FontFace::FontFace(Graphics& graphics,std::string fontfile,int fontsize):
	m_graphics(graphics),
	m_height(0),
	m_font(0)
{
	load(fontfile,fontsize);
}

FontFace::~FontFace()
{
	unload();
}

int FontFace::load(std::string fontfile,int fontsize)
{
	if(!TTF_WasInit())
	{
		TTF_Init();
	}

	unload();

	m_font=TTF_OpenFont(fontfile.c_str(),fontsize);

	if(!m_font)
	{
		std::cerr << TTF_GetError() << "\n";
		return -1;
	}

	m_height=TTF_FontHeight(m_font);

	loadPage(0);

	return 0;
}


void FontFace::unload()
{
	if(m_font)
	{
		TTF_CloseFont(m_font);
		m_font=0;
	}

	m_height=0;
}



void FontFace::draw(std::wstring str,Vector2D pos,float char_height)
{
	if(!m_font)
		return;

	Vector2D char_pos=pos;
	Vector2D char_size=Vector2D(0,char_height);
	Vector2D row_start=pos;
		
	for(size_t i=0;i<str.length();i++)
	{
		if (str[i]>=0x20)
		{
			unsigned int page=str[i]/FONT_PAGE_SIZE;

			loadPage(page);

			FontPage& font_page=m_font_pages[page];
			int rectangle_index=str[i]%FONT_PAGE_SIZE;
			LetterRectangle& letterinfo=m_font_pages[page].letter_rectangles[rectangle_index];
			
			char_size.setX(char_height*(letterinfo.size.getX()/letterinfo.size.getY())/m_graphics.getAspectRatio());
			
			font_page.letters.drawClipped(char_pos,char_size,letterinfo.position,letterinfo.size);

			char_pos+=Vector2D(char_size.getX(),0);
		}
		else
		{
			switch(str[i])
			{
				case '\n':
					char_pos=row_start+Vector2D(0,char_height);
					row_start=char_pos;
					break;

				default:
					break;
			}
		}
	}
}
#if 0
void FontFace::drawWrapped(std::wstring str,float x,float y,float height,float area_width,float area_height)
{
	std::wstring res_str, stub;
	res_str.clear();
	stub.clear();
	size_t word_start, word_end;
	word_start = word_end = 0;
	int max_rows = area_width / getTextSize(L"X").getY() + 1;
	int rows_processed = 0;

	while ((word_end != std::wstring::npos) && (rows_processed <= max_rows))
	{
		word_start = word_end + 1;
		word_end = str.find(L" ",word_start);
		stub = str.substr(word_start-1,word_end - word_start + 1);

		if (getTextSize(res_str + stub).getX() > size.getX())
		{
			res_str += L"\n";
			//remember that space on front of stub?
			res_str += stub.substr(1);
			++rows_processed;
		}
		else
		{
			res_str += stub;
		}
	}

	draw(res_str, x, y, height);
}
#endif
Vector2D FontFace::getTextSize(std::wstring str,float char_height)
{
	if(!m_font)
	{std::cout<<"asd"<<std::endl;
		return Vector2D(0,0);
	}

	float highestw=0;
	float w=0;
	float h=char_height;

	for(size_t i=0;i<str.length();i++)
	{
		if (str[i]>=0x20)
		{
			unsigned int page=str[i]/FONT_PAGE_SIZE;

			loadPage(page);
			
			FontPage& font_page=m_font_pages[page];
			int rectangle_index=str[i]%FONT_PAGE_SIZE;
			LetterRectangle& letterinfo=font_page.letter_rectangles[rectangle_index];
			
			w+=char_height*(letterinfo.size.getX()/letterinfo.size.getY())/m_graphics.getAspectRatio();
		}
		else
		{
			switch(str[i])
			{
				case '\n':
					h+=char_height;
					if(w>highestw)
					{
						highestw=w;
					}
					w=0;
					break;

				default:
					break;
			}
		}

	}

	if(w>highestw)
	{
		highestw=w;
	}

	return Vector2D(highestw,h);
}

int FontFace::loadPage(unsigned int pagenum)
{
	if(m_font_pages.find(pagenum)!=m_font_pages.end())
		return 0;

	//Calculate the size of the needed surface

	int w; 	//Width of the current glyph
	int h; 	//hieght of the current glyph

	int texture_width=0;
	int texture_height=m_height;

	int max_texture_size;

	glGetIntegerv(GL_MAX_TEXTURE_SIZE,&max_texture_size);

	Vector2D current_pos=Vector2D(0,0);

	uint16_t ch[2]={0,0};

	for (int i=0;i<FONT_PAGE_SIZE; i++)
	{
		int unicode=pagenum*FONT_PAGE_SIZE+i;

		if(unicode>=0x20)
		{
			ch[0]=unicode;

			if(TTF_SizeUNICODE(m_font,ch,&w,&h))
			{
				std::cerr << SDL_GetError() << "\n";
				return -1;
			}

			if(current_pos.getX()+w>max_texture_size)
			{
				if(current_pos.getX()>texture_width)
				{
					texture_width=current_pos.getX();
				}
				
				current_pos.setX(0);
				current_pos+=Vector2D(0,m_height);
				texture_height+=m_height;
			}

			m_font_pages[pagenum].letter_rectangles[i].position=current_pos;
			m_font_pages[pagenum].letter_rectangles[i].size=Vector2D(w,m_height);
					
			current_pos+=Vector2D(w,0);

			
		}		
	}

	if(texture_width==0)
	{
		texture_width=current_pos.getX();	
	}

	SDL_Surface* letters=SDL_CreateRGBSurface(SDL_SWSURFACE,texture_width,texture_height,32,RMASK,GMASK,BMASK,AMASK);
	
	if(!letters)
	{
		std::cerr<<"Cannot create surface for font: "<<SDL_GetError()<<std::endl;
		return -1;
	}

	SDL_SetAlpha(letters,0,SDL_ALPHA_OPAQUE);

	//render the letters
	SDL_Surface* temp;
	
	for(int i=0;i<FONT_PAGE_SIZE;i++)
	{
		int unicode=pagenum*FONT_PAGE_SIZE+i;		
		
		if(unicode>=0x20)
		{
			ch[0]=unicode;
		
			SDL_Color color={255,255,255};

			if(!m_font_pages[pagenum].letter_rectangles[i].size.getX())
				continue;
		
			temp=TTF_RenderUNICODE_Blended(m_font,ch,color);
			
			if(!temp)
			{
				std::cerr<<"Cannot render glyph number "<<unicode<<": "<<SDL_GetError()<<std::endl;
				return -1;
			}

			SDL_SetAlpha(temp,0,SDL_ALPHA_OPAQUE);
		
			SDL_Rect clip={	m_font_pages[pagenum].letter_rectangles[i].position.getX(),
					m_font_pages[pagenum].letter_rectangles[i].position.getY(),
					texture_width,
					texture_height};

			if(SDL_BlitSurface(temp,0,letters,&clip))
			{
				std::cerr<<"Cannot blit glyph number "<<unicode<<": "<<SDL_GetError()<<std::endl;
				return -1;
			}
			
			SDL_FreeSurface(temp);	
			
		}	
	}
	
	m_font_pages[pagenum].letters.loadSurface(letters,0);
	m_font_pages[pagenum].letters.setFilter(TRILINEAR);
	SDL_FreeSurface(letters);	

	return 0;
}

