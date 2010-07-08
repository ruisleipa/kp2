#include "fontface.hpp"

#include "graphics.hpp"
#include "shared/string.hpp"

#include <sstream>
#include <iterator>

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
	
	m_name=fontfile;

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

	m_name="";
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
			int rectangle_index=str[i]%FONT_PAGE_SIZE;

			/*
			This is a workaround to a problem where using large
			amount of different qlyphs causes memory usage to grow
			way too large. We only allow basic glyphs (page 0).
			Page 32 is allowed because the euro sign resides there.
			If a glyph doesn't reside on those pages, we display a
			question mark instead.
			TODO: Rework the class to use some kind of glyph level
			caching. Not a top priority however.
			*/
			if(page!=0 && page!=32)
			{
				page='?'/FONT_PAGE_SIZE;
				rectangle_index='?'%FONT_PAGE_SIZE;
			}
			
			loadPage(page);

			FontPage& font_page=m_font_pages[page];
			
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

void FontFace::drawWrapped(std::wstring str,Vector2D pos,Vector2D size,float char_height)
{
#if 0
	float row_size = 0;
	int rows_processed = 0;
	size_t word_start = 0, word_end = 0;
	std::wstring res_str, stub;
	res_str.clear();
	stub.clear();

	while (word_end != std::wstring::npos)
	{
		//If text goes beyond our boundaries, it'll be cropped anyway.
		if (getTextSize(L"X",char_height).getY()*rows_processed >= size.getY())
		{
			stub = str.substr(word_start);
			res_str += stub;
			break;
		}
		

		word_start = word_end+1;
		//we want to skip those whitespaces,
		//but we still must cut from the beginning of the string
		if (word_end == 0)
			word_start = 0;

		word_end = str.find(L" ",word_start);
		row_size += getTextSize(stub + L" ",char_height).getX();

		stub = str.substr(word_start,word_end-word_start);
		
		
		if(stub.find(L"\n") != std::wstring::npos)
		{
			row_size = 0;
			rows_processed++;
		}
		if (getTextSize(stub,char_height).getX()+row_size >= size.getX())
		{
			row_size = 0;
			res_str += L"\n";
			rows_processed++;
		}		
		
		res_str += stub + L" ";
	}

	draw(res_str, pos, char_height);
	
#else
	/*
	Split the input to words
	*/	
	std::wstringstream ss(str);
	std::vector<std::wstring> words;
	
	while(!ss.eof())
	{
		std::wstring word;
		
		std::getline(ss,word,ss.widen(' '));
		
		size_t newlinepos;
		
		while((newlinepos=word.find(L"\n")) != std::string::npos)
		{
			words.push_back(word.substr(0,newlinepos+1));
			word.erase(0,newlinepos+1);
		}		
		
		if(word.size())
			words.push_back(word);
	}	

	/*
	Do layout.
	*/	
	int max_rows = size.getY() / getTextSize(L"X",char_height).getY() + 1;
	Vector2D rowsize;
	std::wstring final_string;
	
	std::vector<std::wstring>::iterator i;
	
	for(i=words.begin();i!=words.end();++i)
	{
		rowsize+=getTextSize((*i),char_height);
	
		if(rowsize.getX()>size.getX())
		{
			final_string.append(L"\n");
			final_string.append((*i));
			final_string.append(L" ");
			
			rowsize=Vector2D(0,0);			
			rowsize+=getTextSize((*i),char_height);
			rowsize+=getTextSize(L" ",char_height);
		}
		else if((*i).at((*i).size()-1)=='\n')
		{
			final_string.append((*i));
		
			rowsize=Vector2D(0,0);
		}
		else
		{
			final_string.append((*i));
			final_string.append(L" ");
			
			rowsize+=getTextSize(L" ",char_height);
		}
	}

	draw(final_string, pos, char_height);
#endif
}

Vector2D FontFace::getTextSize(std::wstring str,float char_height)
{
	if(!m_font)
	{
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
	
	std::stringstream tag;
	tag<<m_name<<": Page "<<pagenum;
	
	m_font_pages[pagenum].letters.loadSurface(letters,tag.str());
	m_font_pages[pagenum].letters.setFilter(TRILINEAR);
	SDL_FreeSurface(letters);	

	return 0;
}

