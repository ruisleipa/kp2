#ifndef SCISSOR_HPP
#define SCISSOR_HPP

class Vector2D;
class Window;

class Scissor
{
	public:
		void set(Vector2D pos,Vector2D size);
		void reset();
		
		Scissor(Window& window);
			
	private:
		Window& window;

};

#endif // SCISSOR_HPP
