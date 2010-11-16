#ifndef WIDGET_HPP
#define WIDGET_HPP

#include "graphics/vector2d.hpp"
#include "graphics/window.hpp"
#include "graphics/color.hpp"

#include "events/eventlistener.hpp"
#include "events/keyevent.hpp"
#include "events/mouseevent.hpp"
#include "events/drawevent.hpp"

#include "utils/noncopyable.hpp"

class Container;

class Widget: public EventListener, public NonCopyable
{
	public:
		void setPosition(Vector2D position) __attribute__((__deprecated__));
		void setFactorPosition(Vector2D position);
		void setPixelPosition(Vector2D position);

		void setSize(Vector2D size) __attribute__((__deprecated__));	
		void setFactorSize(Vector2D size);	
		void setPixelSize(Vector2D size);	
		
		void setFluid(bool fluid);
		bool getFluid();
		
		void setVisible(bool visible);
		bool getVisible();
		
		void setBackgroundColor(const Color& color);
		const Color& getBackgroundColor();

		virtual void handleEvent(Event* event);
				
		//legacy functions for size setting
		virtual void resize(Window& window);
		virtual void onResize(Window& window);
		
		Container* getParent();
		
		Widget();
		virtual ~Widget();
	
	protected:	
		bool hasPixelPosition();
		Vector2D getPosition();
		
		bool hasPixelSize();
		Vector2D getSize();	
	
	private:
		void handleDrawEvent(DrawEvent* event);
		
		void setParent(Container* container);
			
		bool visible;
			
		Container* parent;
	
		Vector2D position;
		bool pixelPosition;
		
		Vector2D size;
		bool pixelSize;
		
		bool fluid;
		
		Color backgroundColor;
		
		friend class Container;
};

#include "container.hpp"

#endif // WIDGET_HPP
