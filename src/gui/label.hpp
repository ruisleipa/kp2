#ifndef LABEL_HPP
#define LABEL_HPP

#include "textwidget.hpp"

class Label : public TextWidget
{
	public:
		virtual void onDraw(Window& window);
		
		Label();
		
	private:
};

#endif // LABEL_HPP
