#ifndef EVENTAREA_HPP
#define EVENTAREA_HPP

#include "graphics/window.hpp"
#include "graphics/vector2d.hpp"

class EventArea
{
	public:
		const Vector2D& getPosition() const;
		const Vector2D& getSize() const;
		Window& getWindow() const;
			
		EventArea(Window& window,Vector2D position,Vector2D size);
		
	private:
		Window* window;
		Vector2D position;
		Vector2D size;
		
};

#endif // EVENTAREA_HPP
