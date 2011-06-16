#ifndef GUI_WIDGET_HPP
#define GUI_WIDGET_HPP

#include "graphics/vector2d.hpp"
#include "graphics/window.hpp"
#include "graphics/color.hpp"

#include "events/eventlistener.hpp"
#include "events/keyevent.hpp"
#include "events/mouseevent.hpp"
#include "events/drawevent.hpp"

#include "utils/noncopyable.hpp"
#include "utils/timer.hpp"

class Container;

class Widget: public EventListener, public NonCopyable
{
	public:
		const std::string& getName();
		void setName(const std::string& name);
		
		void setVisible(bool visible);
		bool getVisible();
		
		virtual Vector2D getAutoSize();
		
		void setBackgroundColor(const Color& color);
		const Color& getBackgroundColor();

		Vector2D getLatestSize();
		
		void setToolTip(std::string str);
		
		virtual void handleEvent(Event* event);

		Widget();
		virtual ~Widget();
		
	private:
		void handleDrawEvent(DrawEvent* event);
		void handleMouseMoveEvent(MouseMoveEvent* event);
		void handleMouseOutEvent(MouseOutEvent* event);
		
		std::string name;
		
		bool visible;
		
		Color backgroundColor;
		
		Vector2D latestSize;
		
		std::string toolTip;		
		Timer toolTipTimer;
		Vector2D mousePosition;
		bool mouseOn;
};

#endif
