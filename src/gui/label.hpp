#ifndef LABEL_HPP
#define LABEL_HPP

#include "textwidget.hpp"

class Label : public TextWidget
{
	public:
		virtual void handleEvent(Event* event);
		
		Label();
		
	private:
		void handleDrawEvent(DrawEvent* event);
};

#endif // LABEL_HPP
