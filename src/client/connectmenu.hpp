#ifndef __CONNECTMENU_HPP
#define __CONNECTMENU_HPP

#include "view.hpp"
#include "label.hpp"
#include "button.hpp"
#include "image.hpp"
#include "field.hpp"

class ConnectMenu : public View
{
	public:
		ConnectMenu();

		virtual void calculateLayout();
		virtual void onActivate();
		
	private:

		Texture m_background_texture;
		Image m_background;
		
		Label m_title;

		Label m_hostname_label;
		Field m_hostname_field;
		Label m_port_label;
		Field m_port_field;
				
		class BackButton: public Button
		{
			public:				
				void onClick();
		}m_back_button;
		
		class ConnectButton: public Button
		{
			public:	
				void onClick();
		}m_connect_button;

		std::vector<Vector2D> m_modes;
};

#endif // __CONNECTMENU_HPP
