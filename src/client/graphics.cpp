#include "graphics.hpp"

#include "sdl.hpp"
#include "assert.hpp"
#include "ui.hpp"

#include <iostream>
#include <cstdlib>
#include <GL/glew.h>

Graphics& Graphics::getInstance()
{
	static Graphics instance;

	return instance;
}

void Graphics::printVideoInfo()
{
	std::cout<<"Video mode: "<<m_screen_width<<"x"<<m_screen_height<<"x"<<m_bpp;
	
	if(m_doublebuffer)
		std::cout<<" doublebuffered";
	
	if(m_vsync)
		std::cout<<" vsynced";
	
	if(m_fullscreen)
		std::cout<<" fullscreen";

	std::cout<<std::endl;
}

float Graphics::getAspectRatio()
{
	return float(m_screen_width)/float(m_screen_height);
}

void Graphics::enterGuiMode()
{
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();	
	glOrtho(0,1,1,0,0,1);
	glMatrixMode(GL_MODELVIEW);
}

void Graphics::exitGuiMode()
{
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
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
	
	m_surface = SDL_SetVideoMode(width, height, bpp, flags);

	if(!m_surface)
	{
		std::cerr << "SDL_SetVideoMode(" << width << "," << height << "," << bpp << "," << flags << ") failed: " << SDL_GetError() << std::endl; 	
		return -1;
	}
	
	m_screen_width = m_surface->w;
	m_screen_height = m_surface->h;
	m_bpp = m_surface->format->BitsPerPixel;
	m_fullscreen = m_surface->flags & SDL_FULLSCREEN;
	
	int value;
	if (SDL_GL_GetAttribute(SDL_GL_DOUBLEBUFFER, &value) == -1)
		std::cerr << "SDL_GL_GetAttribute(SDL_GL_DOUBLEBUFFER, ) returned -1" << std::endl;
	else
		m_doublebuffer = value;
		
	if (SDL_GL_GetAttribute(SDL_GL_SWAP_CONTROL, &value) == -1)
		std::cerr << "SDL_GL_GetAttribute(SDL_GL_SWAP_CONTROL,) returned -1" << std::endl;
	else
		m_vsync = value;
	
	glViewport(0, 0, m_screen_width, m_screen_height);
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
	
	refreshTextures();
	
	Ui::getInstance().calculateLayouts();
	
	return 0;
}

class Compare
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
	std::set<Vector2D,Compare> modelist;
	
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
	std::set<Vector2D,Compare>::iterator i;
		
	for(i=modelist.begin();i!=modelist.end();++i)
	{
		final.push_back(*i);
	}	

	return final;
}

bool Graphics::isVsynced()
{
	return m_vsync;
}

bool Graphics::isFullscreen()
{
	return m_fullscreen;
}

void Graphics::resize(Vector2D size)
{
	std::cout<<size<<std::endl;

	setVideoMode(size.getX(),size.getY(),m_bpp,m_fullscreen,m_vsync,m_doublebuffer);
}

Vector2D Graphics::getDisplaySize()
{
	return Vector2D(m_screen_width,m_screen_height);
}

Graphics::Graphics()
{
	//make sure SDL is initalized
	Sdl::getInstance();	
}

void Graphics::addTexture(Texture* texture)
{
	assert(texture != 0);

	if(texture)
		m_textures.insert(texture);
}

void Graphics::removeTexture(Texture* texture)
{
	m_textures.erase(texture);
}

void Graphics::refreshTextures()
{
	std::set<Texture*>::iterator i;
		
	for(i=m_textures.begin();i!=m_textures.end();++i)
	{
		(*i)->reuploadTexture();
	}
}

Graphics::~Graphics()
{
	
}

