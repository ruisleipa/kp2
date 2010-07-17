#ifndef CAREERMENU_HPP
#define CAREERMENU_HPP

#include "container.hpp"
#include "label.hpp"
#include "button.hpp"
#include "image.hpp"
#include "field.hpp"

class CareerMenu : public Container
{
	public:
		CareerMenu();

		virtual void onResize(Graphics& graphics);
		virtual void onDraw(Graphics& graphics);
		virtual void onConnectionEvent(Connection& connection);
		
		void changeBackground();
		
	private:
		void garageButtonClick();
		void tuningButtonClick();
		void financeButtonClick();
		void raceButtonClick();
		
		Image m_background;
		Image m_background_back;
		
		Texture m_sidebar_texture;
		Image m_sidebar;
		
		Label m_info_label;
			
		Button m_garage_button;
		Button m_tuning_button;
		Button m_finance_button;
		Button m_race_button;
		
		std::vector<Texture> m_background_files;
		Timer m_bg_chage_timer;

};

#endif // CAREERMENU_HPP
