#ifndef EVENT_HPP
#define EVENT_HPP

#include "eventarea.hpp"
#include "graphics/vector2d.hpp"

class Event
{
	public:
		const Vector2D& getAreaPosition();
		virtual void moveOrigin(const Vector2D& offset);
		
		const Vector2D& getAreaSize();		
		void setAreaSize(const Vector2D& size);
		
		Window& getWindow();		
				
		Event(const EventArea& area);
		
	private:
		EventArea area;
		
};

#endif // DRAWEVENT_HPP
