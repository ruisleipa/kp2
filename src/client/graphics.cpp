#include "graphics.hpp"

#include "sdl.hpp"
#include "assert.hpp"
#include "ui.hpp"
#include "texture.hpp"
#include "events.hpp"
#include "shared/inifile.hpp"

#include <iostream>
#include <cstdlib>
#include <GL/glew.h>

void Graphics::printVideoInfo()
{
	Vector2D displaysize=getDisplaySize();

	std::cout<<"Video mode: "<<displaysize.getX()<<"x"<<displaysize.getY()<<"x"<<getBitsPerPixel();
	
	if(isDoubleBuffered())
		std::cout<<" doublebuffered";
	
	if(isVsynced())
		std::cout<<" vsynced";
	
	if(isFullScreen())
		std::cout<<" fullscreen";

	std::cout<<std::endl;
}

float Graphics::getAspectRatio()
{
	return m_aspect_ratio;
}

void Graphics::enterGuiMode()
{
	if(m_gui)
		return;
	
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();	
	glOrtho(0,1,1,0,0,1);
	glMatrixMode(GL_MODELVIEW);
	
	m_gui=true;
}

void Graphics::exitGuiMode()
{
	if(!m_gui)
		return;
	
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
	
	m_gui=false;
}

int Graphics::setVideoMode(int width,int height,int bpp,bool fullscreen,bool vsync,bool doublebuffer)
{
	if (SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER,doublebuffer) == -1)
		std::cerr << "SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER," << doublebuffer << ") returned -1" << std::endl;

	if (SDL_GL_SetAttribute(SDL_GL_SWAP_CONTROL,vsync) == -1)
		std::cout << "SDL_GL_SetAttribute(SDL_GL_SWAP_CONTROL," << vsync << ") returned -1" << std::endl;

	int flags=SDL_OPENGL;

	if(fullscreen)
		flags|=SDL_FULLSCREEN;
	
	bool gui=m_gui;
	
	exitGuiMode();
	
	m_surface = SDL_SetVideoMode(width, height, bpp, flags);
	
	if(gui)
		enterGuiMode();

	if(!m_surface)
	{
		std::cerr << "SDL_SetVideoMode(" << width << "," << height << "," << bpp << "," << flags << ") failed: " << SDL_GetError() << std::endl; 	
		return -1;
	}
	
	Vector2D displaysize=getDisplaySize();	
		
	if(fullscreen)
	{
		std::vector<Vector2D> modelist=getVideoModes();
		Vector2D biggestmode=modelist.back();
		
		m_aspect_ratio=biggestmode.getX()/biggestmode.getY();
	}
	else
	{
		m_aspect_ratio=displaysize.getX()/displaysize.getY();
	}
	
	glViewport(0,0,displaysize.getX(),displaysize.getY());
	glEnable(GL_TEXTURE_2D);
	
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);

	GLenum retval = glewInit();

	if(retval != GLEW_OK)
	{
		std::cerr<<"glewInit() failed: "<< glewGetErrorString(retval) <<std::endl; 	
		return -1;
	}

	printVideoInfo();
	
	Texture::reuploadTextures();
	
	m_events.resize(*this);
	
	return 0;
}

class ModeCompare
{
	public:
		bool operator() (const Vector2D& lhs, const Vector2D& rhs) const
		{
			if(lhs.getX() == rhs.getX())
				return lhs.getY()<rhs.getY();
			else
				return lhs.getX()<rhs.getX();
		}
};

std::vector<Vector2D> Graphics::getVideoModes()
{
	std::set<Vector2D,ModeCompare> modelist;
	
	SDL_Rect** modes = SDL_ListModes(NULL, SDL_OPENGL|SDL_FULLSCREEN);

	if (modes == (SDL_Rect**)0)
	{
		std::cout<<"No modes available!\n"<<std::endl;
	}

	/* Check if our resolution is restricted */
	if (modes == (SDL_Rect**)-1)
	{
		std::cout<<"All resolutions available.\n"<<std::endl;
	}
	else
	{
		for (int i=0; modes[i]; ++i)
			modelist.insert(Vector2D(modes[i]->w,modes[i]->h));
	}
	
	std::vector<Vector2D> final;
	std::set<Vector2D,ModeCompare>::iterator i;
		
	for(i=modelist.begin();i!=modelist.end();++i)
	{
		final.push_back(*i);
	}	

	return final;
}

bool Graphics::isDoubleBuffered()
{
	int value;

	SDL_GL_GetAttribute(SDL_GL_DOUBLEBUFFER,&value);

	return value;
}

bool Graphics::isVsynced()
{
	int value;

	SDL_GL_GetAttribute(SDL_GL_SWAP_CONTROL,&value);

	return value;
}

bool Graphics::isFullScreen()
{
	return m_surface->flags & SDL_FULLSCREEN;
}

int Graphics::getBitsPerPixel()
{
	return m_surface->format->BitsPerPixel;	
}

void Graphics::resize(Vector2D size)
{
	std::cout<<size<<std::endl;

	setVideoMode(size.getX(),size.getY(),getBitsPerPixel(),isFullScreen(),isVsynced(),isDoubleBuffered());
}

Vector2D Graphics::getDisplaySize()
{
	return Vector2D(m_surface->w,m_surface->h);
}

const std::string VIDEO_CONFIG="cfg/video.cfg";

Graphics::Graphics(Sdl& sdl,Events& events):
	m_sdl(sdl), 
	m_events(events),
	m_surface(0),
	m_aspect_ratio(1),
	m_gui(false)
{
	IniFile videosettings(VIDEO_CONFIG);

	int width,height,fullscreen,vsync,filter;

	if(!videosettings.getValue("width",width) || !videosettings.getValue("height",height))
	{
		width=640;
		height=480;
	}

	if(!videosettings.getValue("fullscreen",fullscreen))
		fullscreen=0;
	if(!videosettings.getValue("vsync",vsync))
		vsync=1;
	if(!videosettings.getValue("filter",filter))
		filter=LINEAR;
		
	SDL_WM_SetCaption("Kiihdytyspeli 2","Kiihdytyspeli 2");
	
	setVideoMode(width,height,32,fullscreen,vsync,true);
	Texture::setFilterLimit((TextureFilter)filter);
}

Graphics::~Graphics()
{
	IniFile videosettings(VIDEO_CONFIG);

	int width,height,fullscreen,vsync,filter;
	
	Vector2D displaysize=getDisplaySize();
	fullscreen=isFullScreen();
	vsync=isVsynced();
	filter=Texture::getFilterLimit();		
	
	videosettings.setValue("fullscreen",fullscreen);
	videosettings.setValue("vsync",vsync);
	videosettings.setValue("width",displaysize.getX());
	videosettings.setValue("height",displaysize.getY());
	videosettings.setValue("filter",filter);
	
	videosettings.save(VIDEO_CONFIG);
}

