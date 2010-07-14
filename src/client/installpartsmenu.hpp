#ifndef INSTALLPARTSMENU_HPP
#define INSTALLPARTSMENU_HPP

#include "container.hpp"
#include "label.hpp"
#include "button.hpp"
#include "image.hpp"
#include "field.hpp"
#include "listbox.hpp"

class InstallpartsMenu : public Container
{
	public:
		InstallpartsMenu();

		virtual void onResize(Graphics& graphics);
		virtual void onShow();
		
	private:
		Texture m_background_texture;
		Image m_background;
		
		Label m_car_title;		
		Label m_part_title;
		
		Label m_car_part_list;		
		Listbox m_part_list;
		
		class InstallButton: public Button
		{
			public:				
				void onClick();
		}m_install_button;
		
		class SellButton: public Button
		{
			public:				
				void onClick();
		}m_sell_button;
};

#endif // INSTALLPARTSMENU_HPP
