#ifndef __PARTSHOPMENU_HPP
#define __PARTSHOPMENU_HPP

#include "container.hpp"
#include "label.hpp"
#include "button.hpp"
#include "image.hpp"
#include "field.hpp"
#include "listbox.hpp"

class PartshopMenu : public Container
{
	public:
		PartshopMenu();

		virtual void onResize(Graphics& graphics);
		virtual void onShow();
		
	private:
		Texture m_background_texture;
		Image m_background;
		
		Texture m_part_texture;
		Image m_part_image;
		
		Label m_category_info;
		
		Listbox m_category_list;
		
		Label m_part_price;		
		Listbox m_part_list;
		
		class BuyButton: public Button
		{
			public:				
				void onClick();
		}m_buy_button;
};

#endif // __PARTSHOPMENU_HPP
