#ifndef __FIELD_HPP
#define __FIELD_HPP

#include "textwidget.hpp"

class Field : public TextWidget
{
	public:
		virtual void draw(Graphics& graphics);
		virtual void keyDown(KeyEvent event);
		
		virtual void focus();
		virtual void blur();
		
		Field();
	
	protected:
		virtual bool doAutoSizeOnChange();
		
	private:
		size_t m_cursorpos;
		
		bool m_focused;
};

#endif // __FIELD_HPP
