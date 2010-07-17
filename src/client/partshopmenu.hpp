#ifndef PARTSHOPMENU_HPP
#define PARTSHOPMENU_HPP

#include "container.hpp"
#include "columnlayoutcontainer.hpp"
#include "label.hpp"
#include "button.hpp"
#include "image.hpp"
#include "field.hpp"
#include "listbox.hpp"

class PartshopMenu : public Container
{
	public:
		PartshopMenu(Connection& connection);

		virtual void onResize(Graphics& graphics);
		virtual void onShow();
		
	private:
		void categoryChangeHandler();
	
		Connection& m_connection;
	
		Texture m_background_texture;
		Image m_background;
		
		ColumnLayoutContainer m_top_row;
		
		Texture m_part_texture;
		Image m_part_image;		
		Label m_category_info;
		
		ColumnLayoutContainer m_bottom_row;
		
		Listbox m_category_list;		
		Listbox m_part_list;
		
		Label m_part_info;
		
		Button m_buy_button;
};

#endif // PARTSHOPMENU_HPP
