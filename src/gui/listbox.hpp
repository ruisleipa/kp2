#ifndef LISTBOX_HPP
#define LISTBOX_HPP

#include "activetextwidget.hpp"
#include "timer.hpp"
#include "callback/callback.hpp"

#include <vector>

class Listbox : public TextWidget
{
	public:
		virtual void onDraw(Graphics& graphics);
		virtual void onResize(Graphics& graphics);		
	
		virtual void onMouseDown(MouseEvent event);
		virtual void onMouseUp(MouseEvent event);
		virtual void onMouseOut();
		
		void setChangeHandler(Callback0 handler);
		
		Listbox();
		
		void addItem(std::string item,int tag=0);
		void clearItems();
		
		int getCurrentItemTag();
		std::string getCurrentItemString();
		
		int getIndex();
		void setIndex(int index);		
		
		virtual bool doAutoSizeOnChange();
		
	private:
		int m_index;		
		
		float m_scroll_offset;
		float m_scroll_pending;
		Timer m_scroll_timer;

		float m_button_height;
		
		Callback0 m_change_handler;
		
		static Texture m_arrow_up;
		static Texture m_arrow_down;
		static bool m_textures_loaded;		
		
		class Item
		{
			public:
				std::wstring m_string;
				int m_tag;
		};
		
		std::vector<Item> m_items;
};

#endif // LISTBOX_HPP

