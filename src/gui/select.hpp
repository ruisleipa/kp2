#ifndef SELECT_HPP
#define SELECT_HPP

#include "activetextwidget.hpp"

#include <tr1/functional>
#include <vector>

class Select : public ActiveTextWidget
{
	public:
		virtual void handleEvent(Event* event);
			
		Select();
		void setChangeHandler(std::tr1::function<void()> handler);
		
		void addItem(std::string item);
		void clearItems();
		
		int getIndex();
		void setIndex(int index);
		
	private:
		void handleMouseDownEvent(MouseDownEvent* event);
	
		int m_index;
		
		std::tr1::function<void()> changeHandler;		
		std::vector<std::wstring> m_items;
};

#endif // SELECT_HPP

