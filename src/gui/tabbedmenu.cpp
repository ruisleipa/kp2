#include "tabbedmenu.hpp"

const float PADDING=0.02;

#include "utils/string.hpp"

TabbedMenu::TabbedMenu()
{
	setSize(Vector2D(1,1));
	
	buttonContainer.setSize(Vector2D(1,0.2));
	
	tabContainer.setPosition(Vector2D(0,buttonContainer.getSize().getY()));
	tabContainer.setSize(Vector2D(1.0,1-buttonContainer.getSize().getY()));
	
	addWidget(buttonContainer);
	addWidget(tabContainer);	
}

void TabbedMenu::addTab(const std::string& label,Widget& widget)
{
	std::tr1::shared_ptr<Button> button(new Button);
	
	button->setText(label);
	button->setClickHandler(std::tr1::bind(&Container::showOnlyWidget,&tabContainer,convertToString(&widget)));
	
	buttons.push_back(button);
	
	tabContainer.addWidget(convertToString(&widget),widget);
	
	buttonContainer.addWidget(*button);
}
