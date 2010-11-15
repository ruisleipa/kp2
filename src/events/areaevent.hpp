#ifndef AREAEVENT_HPP
#define AREAEVENT_HPP

#include "event.hpp"

#include "eventarea.hpp"
#include "graphics/vector2d.hpp"

class AreaEvent: public Event
{
	public:
		const Vector2D& getAreaPosition();
		virtual void moveOrigin(const Vector2D& offset);
		
		const Vector2D& getAreaSize();		
		void setAreaSize(const Vector2D& size);
		
		Window& getWindow();		
				
		AreaEvent(const EventArea& area);
		
	private:
		EventArea area;
		
};

#endif // AREAEVENT_HPP
