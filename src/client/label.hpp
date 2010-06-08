#ifndef __LABEL_HPP
#define __LABEL_HPP

#include "textwidget.hpp"

class Label : public TextWidget
{
	public:
		virtual void draw(Graphics& graphics);
		
		Label();
		
	private:
};

#endif // __LABEL_HPP
