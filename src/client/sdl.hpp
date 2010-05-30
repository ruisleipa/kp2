#ifndef __SDL_HPP
#define __SDL_HPP

#include <SDL/SDL.h>

class Sdl
{
	public:
		static Sdl& getInstance();

		~Sdl();

	private:
		Sdl();
};

#endif // __SDL_HPP
