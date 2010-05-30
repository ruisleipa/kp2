#ifndef __SELECT_HPP
#define __SELECT_HPP

#include "activetextwidget.hpp"

#include <vector>

class Select : public ActiveTextWidget
{
	public:
		virtual void onChange();
	
		virtual void mouseDown(MouseEvent event);
		
		Select();
		
		void addItem(std::string item);
		void clearItems();
		
		int getIndex();
		void setIndex(int index);
		
	private:
		int m_index;
		
		std::vector<std::wstring> m_items;
};

#endif // __SELECT_HPP

