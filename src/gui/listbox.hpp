#ifndef LISTBOX_HPP
#define LISTBOX_HPP

#include "activetextwidget.hpp"
#include "utils/timer.hpp"

#include <tr1/functional>
#include <vector>

class Listbox : public TextWidget
{
	public:
		virtual void onDraw(DrawEvent event);
		virtual void onResize(Window& window);		
	
		virtual void onMouseDown(MouseEvent event);
		virtual void onMouseUp(MouseEvent event);
		virtual void onMouseOut();
		
		void setChangeHandler(std::tr1::function<void()> handler);
		
		Listbox();
		
		void addItem(std::string item,int tag=0);
		void clearItems();
		
		int getCurrentItemTag();
		std::string getCurrentItemString();
		
		int getIndex();
		void setIndex(int index);		
		
		virtual bool doAutoSizeOnChange();
		
	private:
		int index;		
		
		float scrollOffset;
		float scrollPending;
		Timer scrollTimer;

		float buttonHeight;
		
		std::tr1::function<void()> m_change_handler;
		
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

