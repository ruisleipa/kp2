#ifndef SELECT_HPP
#define SELECT_HPP

#include "activetextwidget.hpp"

#include <tr1/functional>
#include <vector>

class Select : public ActiveTextWidget
{
	public:
		virtual void handleEvent(Event* event);
		
		void setChangeHandler(std::tr1::function<void()> handler);
		
		void addItem(std::string item);
		void clearItems();
		
		int getIndex();
		void setIndex(int index);
		
		Select();
		
	private:
		void handleMouseDownEvent(MouseDownEvent* event);
	
		int selectedIndex;
		std::vector<std::wstring> items;
		
		std::tr1::function<void()> changeHandler;
};

#endif // SELECT_HPP

