#include "sdl.hpp"

#include <cstdlib>
#include <iostream>

#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>
#include <SDL/SDL_net.h>

Sdl::Sdl()
{
	if(SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		std::cerr<<"SDL_Init Failed: "<<SDL_GetError()<<std::endl;
		exit(1);
	}
	
	if(TTF_Init() == -1)
	{
		std::cerr<<"TTF_Init Failed: "<<TTF_GetError()<<std::endl;
		exit(1);
	}
}

Sdl::~Sdl()
{
	TTF_Quit();
	SDL_Quit();
}
