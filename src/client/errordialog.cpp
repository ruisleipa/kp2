#include "errordialog.hpp"

#include "gui/label.hpp"
#include "gui/button.hpp"

void ErrorDialog::showMessage(const std::string& title, const std::string& message)
{
	getChildByName<Label>("title").setText(title);
	getChildByName<Label>("message").setText(message);
	
	errorSound.play();
	
	setVisible(true);
}

ErrorDialog::ErrorDialog():
	Menu("data/ui/errordialog.ui")
{
	errorSound.load("data/sounds/error.wav");
	
	getChildByName<Button>("closeButton").setClickHandler(std::tr1::bind(&Widget::setVisible, this, false));
}
