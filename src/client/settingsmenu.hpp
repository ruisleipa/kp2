#ifndef __SETTINGSMENU_HPP
#define __SETTINGSMENU_HPP

#include "view.hpp"
#include "label.hpp"
#include "select.hpp"
#include "button.hpp"
#include "image.hpp"

class SettingsMenu : public View
{
	public:
		SettingsMenu();

		virtual void calculateLayout();
		virtual void onActivate();
		
	private:

		Texture m_background_texture;
		Image m_background;
		
		Label m_title;

		Label m_resolution_label;
		Select m_resolution_select;
		Label m_fullscreen_label; 
		Select m_fullscreen_select;
		Label m_vsync_label; 
		Select m_vsync_select;
		
		class BackButton: public Button
		{
			public:				
				void onClick();
		}m_back_button;
		
		class ApplyButton: public Button
		{
			public:	
				void onClick();
		}m_apply_button;

		std::vector<Vector2D> m_modes;
};

#endif // __SETTINGSMENU_HPP
