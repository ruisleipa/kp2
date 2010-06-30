#ifndef __FIELD_HPP
#define __FIELD_HPP

#include "textwidget.hpp"

class Field : public TextWidget
{
	public:
		virtual void onDraw(Graphics& graphics);
		virtual void onKeyDown(KeyEvent event);
		
		virtual void onFocus();
		virtual void onBlur();
		
		Field();
	
	protected:
		virtual bool doAutoSizeOnChange();
		
	private:
		size_t m_cursorpos;
		
		bool m_focused;
};

#endif // __FIELD_HPP
