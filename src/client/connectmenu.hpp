#ifndef CONNECTMENU_HPP
#define CONNECTMENU_HPP

#include "container.hpp"
#include "label.hpp"
#include "button.hpp"
#include "image.hpp"
#include "field.hpp"

class ConnectMenu : public Menu
{
	public:
		ConnectMenu();

		virtual void calculateLayout();
		virtual void onActivate();
		
	private:
		void backClickHandler();
		void connectClickHandler();

		Texture m_background_texture;
		Image m_background;
		
		Label m_title;

		Label m_hostname_label;
		Field m_hostname_field;
		Label m_port_label;
		Field m_port_field;
				
		Button m_back_button;
		Button m_connect_button;

		std::vector<Vector2D> m_modes;
};

#endif // CONNECTMENU_HPP
