#include "select.hpp"

#include "shared/string.hpp"
#include "assert.hpp"
#include "scissor.hpp"
#include "ui.hpp"

#include <GL/gl.h>

void Select::onChange()
{
	
}

void Select::mouseDown(MouseEvent event)
{
	ActiveTextWidget::mouseDown(event);

	if(m_index == -1)
		return;

	if(event.isButtonDown(MouseEvent::LEFT) || event.isButtonDown(MouseEvent::WHEELDOWN))
	{
		if(m_index==m_items.size()-1)
			setIndex(0);
		else
			setIndex(getIndex()+1);
	}
		
	if(event.isButtonDown(MouseEvent::RIGHT) || event.isButtonDown(MouseEvent::WHEELUP))
	{
		if(m_index==0)
			setIndex(m_items.size()-1);
		else
			setIndex(getIndex()-1);
	}
}

void Select::addItem(std::string item)
{
	if(m_index == -1)
		setIndex(0);
		
	m_items.push_back(convertToWideString(item));
}

void Select::clearItems()
{
	m_items.clear();
	m_index=-1;
}

int Select::getIndex()
{
	return m_index;
}

void Select::setIndex(int index)
{
	if(index >= 0 && index < m_items.size())
	{
		m_index=index;
		
		setText(m_items[m_index]);
	}
}

Select::Select()
{
	m_index=-1;

	setFont(Ui::getInstance().getFont("Select"));
	setActiveFont(Ui::getInstance().getFont("Select.active"));
}

