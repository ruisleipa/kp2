#include "textwidget.hpp"

#include "utils/string.hpp"

void TextWidget::setText(std::string text)
{
	this->text=convertToWideString(text);
	
	if(doAutoSizeOnChange())
		autoSize();
}

std::string TextWidget::getText()
{
	return convertToString(text);
}

void TextWidget::setText(std::wstring text)
{
	this->text=text;
	
	if(doAutoSizeOnChange())
		autoSize();
}

std::wstring TextWidget::getWideText()
{
	return text;
}

void TextWidget::setFont(Font font)
{
	this->font = font;
}

Font& TextWidget::getFont()
{
	return font;
}

void TextWidget::autoSize()
{
	setPixelSize(font.getTextSize(text));
}

TextWidget::TextWidget()
{
	
}

bool TextWidget::doAutoSizeOnChange()
{
	return true;
}

