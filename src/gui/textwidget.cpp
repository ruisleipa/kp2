#include "textwidget.hpp"

#include "utils/string.hpp"

void TextWidget::setText(std::string text)
{
	m_text=convertToWideString(text);
	
	if(doAutoSizeOnChange())
		autoSize();
}

std::string TextWidget::getText()
{
	return convertToString(m_text);
}

void TextWidget::setText(std::wstring text)
{
	m_text=text;
	
	if(doAutoSizeOnChange())
		autoSize();
}

std::wstring TextWidget::getWideText()
{
	return m_text;
}

void TextWidget::setFont(Font font)
{
	m_font=font;
}

Font& TextWidget::getFont()
{
	return m_font;
}

void TextWidget::autoSize()
{
	setSize(m_font.getTextSize(*(getWindow()),m_text));
}

TextWidget::TextWidget()
{
	
}

bool TextWidget::doAutoSizeOnChange()
{
	return false;
}

