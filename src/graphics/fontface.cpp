#include "fontface.hpp"

#include "utils/string.hpp"

#include <sstream>
#include <iterator>

FontFace::FontFace(Window& window,std::string fontfile,int fontsize):
	window(&window),
	height(0)
{
	load(fontfile,fontsize);
}

FontFace::~FontFace()
{
	unload();
}

int FontFace::load(std::string fontfile,int fontsize)
{
	font = std::tr1::shared_ptr<FontFile>(new FontFile(fontfile, fontsize));
	
	height=TTF_FontHeight(font->font);

	loadPage(0);

	return 0;
}


void FontFace::unload()
{
	font.reset();
}

void FontFace::draw(std::wstring str,Vector2D pos)
{
	if(!font)
		return;

	Vector2D char_pos=pos;
	Vector2D char_size=Vector2D(0,height);
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
			caching.
			*/
			if(page!=0 && page!=32)
			{
				page='?'/FONT_PAGE_SIZE;
				rectangle_index='?'%FONT_PAGE_SIZE;
			}
			
			loadPage(page);

			FontPage& font_page=fontPages[page];
			
			LetterRectangle& letterinfo=fontPages[page].letter_rectangles[rectangle_index];
			
			char_size.setX(letterinfo.size.getX());
			
			font_page.letters.drawClipped(char_pos,char_size,letterinfo.position,letterinfo.size);

			char_pos+=Vector2D(char_size.getX(),0);
		}
		else
		{
			switch(str[i])
			{
				case '\n':
					char_pos=row_start+Vector2D(0,height);
					row_start=char_pos;
					break;

				default:
					break;
			}
		}
	}
}

void FontFace::drawWrapped(std::wstring str,Vector2D pos,Vector2D size)
{
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

	int max_rows = size.getY() / getTextSize(L"X").getY() + 1;
	Vector2D rowsize;
	std::wstring final_string;
	
	std::vector<std::wstring>::iterator i;
	
	for(i=words.begin();i!=words.end();++i)
	{
		rowsize+=getTextSize((*i));
	
		if(rowsize.getX()>size.getX())
		{
			final_string.append(L"\n");
			final_string.append((*i));
			final_string.append(L" ");
			
			rowsize=Vector2D(0,0);			
			rowsize+=getTextSize((*i));
			rowsize+=getTextSize(L" ");
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
			
			rowsize+=getTextSize(L" ");
		}
	}

	draw(final_string, pos);
}

Vector2D FontFace::getTextSize(std::wstring str)
{
	if(!font)
	{
		return Vector2D(0,0);
	}

	float highestw=0;
	float w=0;
	float h=height;

	for(size_t i=0;i<str.length();i++)
	{
		if (str[i]>=0x20)
		{
			unsigned int page=str[i]/FONT_PAGE_SIZE;

			loadPage(page);
			
			FontPage& font_page=fontPages[page];
			int rectangle_index=str[i]%FONT_PAGE_SIZE;
			LetterRectangle& letterinfo=font_page.letter_rectangles[rectangle_index];
			
			w+=letterinfo.size.getX();
		}
		else
		{
			switch(str[i])
			{
				case '\n':
					h+=height;
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

void FontFace::freeTextures()
{
	std::map<unsigned long,FontPage>::iterator i;
	
	for(i = fontPages.begin(); i != fontPages.end(); ++i)
	{
		i->second.letters.free();
	}
}

void FontFace::uploadTextures()
{
	std::map<unsigned long,FontPage>::iterator i;
	
	for(i = fontPages.begin(); i != fontPages.end(); ++i)
	{
		i->second.letters.upload();
	}
}

int FontFace::loadPage(unsigned int pagenum)
{
	if(fontPages.find(pagenum)!=fontPages.end())
		return 0;

	//Calculate the size of the needed surface

	int w; 	//Width of the current glyph
	int h; 	//hieght of the current glyph

	int texture_width=0;
	int texture_height=height;

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

			if(TTF_SizeUNICODE(font->font,ch,&w,&h))
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
				current_pos+=Vector2D(0,height);
				texture_height+=height;
			}

			fontPages[pagenum].letter_rectangles[i].position=current_pos;
			fontPages[pagenum].letter_rectangles[i].size=Vector2D(w,height);
					
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

			if(!fontPages[pagenum].letter_rectangles[i].size.getX())
				continue;
		
			temp=TTF_RenderUNICODE_Blended(font->font,ch,color);
			
			if(!temp)
			{
				std::cerr<<"Cannot render glyph number "<<unicode<<": "<<SDL_GetError()<<std::endl;
				return -1;
			}

			SDL_SetAlpha(temp,0,SDL_ALPHA_OPAQUE);
		
			SDL_Rect clip={	fontPages[pagenum].letter_rectangles[i].position.getX(),
					fontPages[pagenum].letter_rectangles[i].position.getY(),
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
	
	fontPages[pagenum].letters=Texture(letters);
	fontPages[pagenum].letters.setFilter(NEAREST);
	SDL_FreeSurface(letters);	

	return 0;
}

