#ifndef __SCISSOR_HPP
#define __SCISSOR_HPP

#include "vector2d.hpp"

class Scissor
{
	public:
		static void set(Vector2D pos,Vector2D size);
		/*static void setClipped(Vector2D pos,Vector2D size,Vector2D* cpos=0,Vector2D* csize=0);
		static void get(Vector2D& pos,Vector2D& size);*/
		static void reset();
};

#endif // __SCISSOR_HPP
