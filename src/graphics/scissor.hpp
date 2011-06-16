#ifndef SCISSOR_HPP
#define SCISSOR_HPP

class Vector2D;
class Window;

#include <GL/glew.h>

class Scissor
{
	public:
		Scissor(Window& window, Vector2D position, Vector2D size);
		~Scissor();
			
	private:
		void convertFromOpenGl(Vector2D& position, Vector2D& size);
		void convertToOpenGl(Vector2D& position, Vector2D& size);
	
		Window& window;
		
		GLint scissorBox[4];
		GLboolean wasScissorEnabled;

};

#endif // SCISSOR_HPP
