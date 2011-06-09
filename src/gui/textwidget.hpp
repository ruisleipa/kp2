#ifndef TEXTWIDGET_HPP
#define TEXTWIDGET_HPP

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
		
		virtual Vector2D getAutoSize();
	
	protected:
	
	private:	
		Font font;		
		std::wstring text;
};

#endif // TEXTWIDGET_HPP
