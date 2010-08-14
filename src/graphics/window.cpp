#include "window.hpp"

#include "texture.hpp"

#include "events/events.hpp"

#include <sstream>
#include <stdexcept>
#include <cstdlib>
#include <GL/glew.h>

float Window::getAspectRatio()
{
	return aspectRatio;
}

void Window::setVideoMode(Vector2D size,int bpp,bool fullscreen)
{
	surfaceSize = size;
	surfaceBpp = bpp;
	surfaceFullscreen = fullscreen;
	
	createSurface();
	
	calculateAspectRatio();
	initOpenGL();
	initGLEW();
}

void Window::createSurface()
{
	int flags=SDL_OPENGL;

	if(surfaceFullscreen)
		flags|=SDL_FULLSCREEN;	
	
	SDL_Surface* newsurface = SDL_SetVideoMode(surfaceSize.getX(), surfaceSize.getY(), surfaceBpp, flags);
	
	if(!newsurface)
	{
		std::stringstream error;
		error << "Cannot create surface ";
		error << surfaceSize.getX() << "x" << surfaceSize.getY() << "x" << surfaceBpp << " ";
		
		if(surfaceFullscreen)
			error << "fullscreen";
			
		throw std::runtime_error(error.str()); 
	}
	
	surface = newsurface;
}

void Window::setAttributes()
{
	if(SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER,1) == -1)
		throw std::runtime_error("Cannot set SDL_GL_DOUBLEBUFFER."); 

	if(SDL_GL_SetAttribute(SDL_GL_SWAP_CONTROL,vsyncPreference) == -1)
		throw std::runtime_error("Cannot set SDL_GL_SWAP_CONTROL."); 
}

void Window::checkAttributes()
{
	int value;

	if(SDL_GL_GetAttribute(SDL_GL_DOUBLEBUFFER,&value) == -1)
		throw std::runtime_error("Cannot check SDL_GL_DOUBLEBUFFER.");
	
	if(value != 1)
		throw std::runtime_error("Unable to set requested doublebuffer state.");
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

std::vector<Vector2D> Window::getPossibleSizes()
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

bool Window::isVsynced()
{
	int value;

	if(SDL_GL_GetAttribute(SDL_GL_SWAP_CONTROL,&value) == -1)
		throw std::runtime_error("Cannot check Vsync state.");

	return value;
}

bool Window::isFullscreen()
{
	return surface->flags & SDL_FULLSCREEN;
}

int Window::getBitsPerPixel()
{
	return surface->format->BitsPerPixel;	
}

Vector2D Window::getSize()
{
	return Vector2D(surface->w,surface->h);
}

Window::Window(Sdl& sdl):
	surface(0),
	isInGuiMode(false)
{
	applyDefaultSettings();
	loadSettings();
		
	SDL_WM_SetCaption("Kiihdytyspeli 2","Kiihdytyspeli 2");
	
	setVideoMode(surfaceSize,surfaceBpp,surfaceFullscreen);
}

Window::~Window()
{
	saveSettings();
}

void Window::calculateAspectRatio()
{
	if(isFullscreen())
	{
		std::vector<Vector2D> modelist=getPossibleSizes();
		Vector2D nativeresolution=modelist.back();
		
		aspectRatio=nativeresolution.getX()/nativeresolution.getY();
	}
	else
	{
		Vector2D displaysize=getSize();
	
		aspectRatio=displaysize.getX()/displaysize.getY();
	}
}

void Window::initOpenGL()
{
	Vector2D displaysize=getSize();
	
	glViewport(0,0,displaysize.getX(),displaysize.getY());
	
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();	
	glOrtho(0,1,1,0,0,1);
	glMatrixMode(GL_MODELVIEW);
	
	glEnable(GL_TEXTURE_2D);
	
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
}

void Window::initGLEW()
{
	GLenum retval = glewInit();

	if(retval != GLEW_OK)
	{
		std::stringstream error;
		error << "glewInit failed: ";
		error << glewGetErrorString(retval);
		error << std::endl;
	
		throw std::runtime_error(error.str()); 	
	}
}

void Window::applyDefaultSettings()
{
	surfaceSize = Vector2D(640,480);
	surfaceBpp = 32;
	surfaceFullscreen = false;
	vsyncPreference = false;
}

const std::string VIDEO_CONFIG="cfg/video.cfg";

void Window::loadSettings()
{
	settings.load(VIDEO_CONFIG);
	
	int width;
	int height;
	int fullscreen;
	int vsync;
	
	if(!settings.getValue("width",width) || !settings.getValue("height",height))
	{
		surfaceSize = Vector2D(width,height);
	}

	settings.getValue("fullscreen",fullscreen);
	settings.getValue("vsync",vsync);
}

void Window::saveSettings()
{
	int width=getSize().getX();
	int height=getSize().getY();
	int fullscreen=isFullscreen();
	int vsync=isVsynced();
	
	settings.setValue("fullscreen",fullscreen);
	settings.setValue("vsync",vsync);
	settings.setValue("width",width);
	settings.setValue("height",height);
	
	settings.save(VIDEO_CONFIG);
}
