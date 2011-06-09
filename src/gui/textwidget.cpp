#include "textwidget.hpp"

#include "utils/string.hpp"

void TextWidget::setText(std::string text)
{
	this->text=convertToWideString(text);
}

std::string TextWidget::getText()
{
	return convertToString(text);
}

void TextWidget::setText(std::wstring text)
{
	this->text=text;
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

Vector2D TextWidget::getAutoSize()
{
	return font.getTextSize(text);
}
