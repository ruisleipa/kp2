#ifndef __NEWLOCALGAMEMENU_HPP
#define __NEWLOCALGAMEMENU_HPP

#include "window.hpp"
#include "label.hpp"
#include "select.hpp"
#include "button.hpp"
#include "image.hpp"
#include "field.hpp"

#include "connection.hpp"

class NewLocalGameMenu : public Window
{
	public:
		NewLocalGameMenu(Connection& connection);

		virtual void onResize(Graphics& graphics);
		virtual void onShow();
		
	private:
		Connection& m_connection;

		Texture m_background_texture;
		Image m_background;
		
		Label m_title;

		Label m_name_label;
		Label m_difficulty_label; 
		
		Field m_name_field;
		Select m_difficulty_select;
		
		class BackButton: public Button
		{
			public:				
				void onClick();
		}m_back_button;
		
		class StartButton: public Button
		{
			public:	
				void onClick();
		}m_start_button;
};

#endif // __NEWLOCALGAMEMENU_HPP
