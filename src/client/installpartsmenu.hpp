#ifndef INSTALLPARTSMENU_HPP
#define INSTALLPARTSMENU_HPP

#include "container.hpp"
#include "label.hpp"
#include "button.hpp"
#include "image.hpp"
#include "field.hpp"
#include "listbox.hpp"
#include "columnlayoutcontainer.hpp"

class InstallpartsMenu : public Menu
{
	public:
		InstallpartsMenu();

		virtual void onResize(Graphics& graphics);
		virtual void onShow();
		
	private:
		Texture m_background_texture;
		Image m_background;
		
		ColumnLayoutContainer m_title_row;
		
		Label m_car_title;		
		Label m_part_title;
		
		ColumnLayoutContainer m_list_row;
		
		Listbox m_car_part_list;		
		Listbox m_part_list;
		
		Button m_install_button;
		Button m_sell_button;
};

#endif // INSTALLPARTSMENU_HPP
