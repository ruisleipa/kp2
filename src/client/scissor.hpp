#ifndef SCISSOR_HPP
#define SCISSOR_HPP

class Vector2D;
class Graphics;

class Scissor
{
	public:
		void set(Vector2D pos,Vector2D size);
		void reset();
		
		Scissor(Graphics& graphics);
			
	private:
		Graphics& m_graphics;

};

#endif // SCISSOR_HPP
