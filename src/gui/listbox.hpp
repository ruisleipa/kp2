#ifndef LISTBOX_HPP
#define LISTBOX_HPP

#include "activetextwidget.hpp"
#include "utils/timer.hpp"

#include <tr1/functional>
#include <vector>

class Listbox : public TextWidget
{
	public:
		void setChangeHandler(std::tr1::function<void()> handler);
		
		Listbox();
		
		void addItem(std::string item,int tag=0);
		void clearItems();
		
		int getCurrentItemTag();
		std::string getCurrentItemString();
		
		int getIndex();
		void setIndex(int newIndex);
		
		virtual bool doAutoSizeOnChange();
		
		virtual void handleEvent(Event* event);
		
		void onResize(Window& window);	
		
	private:
		void handleDrawEvent(DrawEvent* event);		
		void handleMouseDownEvent(MouseDownEvent* event);
		
		int index;		
		
		float scrollOffset;
		float scrollPending;
		Timer scrollTimer;
		
		std::tr1::function<void()> changeHandler;
		
		static Texture arrowUp;
		static Texture arrowDown;
		static bool haveTexturesBeenLoaded;		
		
		class Item
		{
			public:
				std::wstring text;
				int tag;
		};
		
		std::vector<Item> items;
};

#endif // LISTBOX_HPP

