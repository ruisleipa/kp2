#ifndef __TEXTWIDGET_HPP
#define __TEXTWIDGET_HPP

#include "widget.hpp"
#include "font.hpp"
#include <string>

class TextWidget : public Widget
{
	public:
		void setText(std::string text);
		std::string getText();
		
		void setText(std::wstring text);
		std::wstring getWideText();
	
		void setFont(Font font);
		Font& getFont();
		
		void autoSize();
		
		TextWidget();
	
	protected:
		virtual bool doAutoSizeOnChange();
	
	private:	
		Font m_font;
		
		std::wstring m_text;
};

#endif // __TEXTWIDGET_HPP
