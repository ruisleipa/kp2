#ifndef NEWLOCALGAMEMENU_HPP
#define NEWLOCALGAMEMENU_HPP

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
		void backClickHandler();
		void startClickHandler();
	
		Connection& m_connection;

		Texture m_background_texture;
		Image m_background;
		
		Label m_title;

		Label m_name_label;
		Label m_difficulty_label; 
		
		Field m_name_field;
		Select m_difficulty_select;
		
		Button m_back_button;		
		Button m_start_button;
};

#endif // NEWLOCALGAMEMENU_HPP
