#ifndef __LISTBOX_HPP
#define __LISTBOX_HPP

#include "activetextwidget.hpp"

#include <vector>

class Listbox : public TextWidget
{
	public:
		virtual void onDraw(Graphics& graphics);
		virtual void onResize(Graphics& graphics);
	
		virtual void onChange();
	
		virtual void onMouseDown(MouseEvent event);
		
		Listbox();
		
		void addItem(std::string item);
		void clearItems();
		
		int getIndex();
		void setIndex(int index);
		
		virtual bool doAutoSizeOnChange();
		
	private:
		int m_index;
		
		static Texture m_arrow_up;
		static Texture m_arrow_down;
		static bool m_textures_loaded;
		float m_button_height;
		
		std::vector<std::wstring> m_items;
};

#endif // __LISTBOX_HPP

