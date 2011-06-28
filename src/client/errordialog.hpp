#ifndef CLIENT_ERRORDIALOG_HPP
#define CLIENT_ERRORDIALOG_HPP

#include "gui/menu.hpp"
#include "gui/container.hpp"

#include "sounds/sound.hpp"

class ErrorDialog : public Menu
{
	public:
		void showMessage(const std::string& title, const std::string& message);
		
		ErrorDialog();

	private:
		Sound errorSound;

};

#endif
