#ifndef TUNINGMENU_HPP
#define TUNINGMENU_HPP

#include "container.hpp"
#include "label.hpp"
#include "button.hpp"
#include "image.hpp"
#include "field.hpp"

#include "partshopmenu.hpp"
#include "installpartsmenu.hpp"

class TuningMenu : public Menu
{
	public:
		TuningMenu(Connection& connection);

		virtual void onResize(Graphics& graphics);
		virtual void onHide();
		
	private:
		void installClick();
		void buyClick();
		void dynoClick();
		void adjustClick();
		void machiningClick();
	
		PartshopMenu m_partshopmenu;
		InstallpartsMenu m_installpartsmenu;
		
		Button m_install_button;
		Button m_buy_button;
		Button m_dyno_button;
		Button m_adjust_button;
		Button m_machining_button;
		
};

#endif // TUNINGMENU_HPP
