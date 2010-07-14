#ifndef TUNINGMENU_HPP
#define TUNINGMENU_HPP

#include "container.hpp"
#include "label.hpp"
#include "button.hpp"
#include "image.hpp"
#include "field.hpp"

#include "partshopmenu.hpp"
#include "installpartsmenu.hpp"

class TuningMenu : public Container
{
	public:
		TuningMenu(Connection& connection);

		virtual void onResize(Graphics& graphics);
		virtual void onHide();
		
	private:
		PartshopMenu m_partshopmenu;
		InstallpartsMenu m_installpartsmenu;
		
		class InstallButton: public Button
		{
			public:				
				void onClick();
		}m_install_button;
		
		class BuyButton: public Button
		{
			public:				
				void onClick();
		}m_buy_button;
		
		class DynoButton: public Button
		{
			public:				
				void onClick();
		}m_dyno_button;
		
		class AdjustButton: public Button
		{
			public:				
				void onClick();
		}m_adjust_button;
		
		class MachiningButton: public Button
		{
			public:				
				void onClick();
		}m_machining_button;
		
};

#endif // TUNINGMENU_HPP
