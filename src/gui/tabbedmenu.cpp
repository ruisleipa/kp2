#include "tabbedmenu.hpp"

#include "utils/string.hpp"

TabbedMenu::TabbedMenu()
{
	setSize(Vector2D(1,1));
	
	topContainer.setSize(Vector2D(1,1));
	
	addWidget(topContainer);
	
	topContainer.addWidget(buttonContainer);
	topContainer.addWidget(tabContainer);
	
	tabContainer.setFluid(true);
	tabContainer.setBackgroundColor(Color(1,1,1,0.5));
	
	buttonContainer.showOuterPadding(false);
}

void TabbedMenu::addTab(const std::string& label,Widget& widget)
{
	std::tr1::shared_ptr<Button> button(new Button);
	
	button->setText(label);
	button->autoSize();
	button->setClickHandler(std::tr1::bind(&Container::showOnlyWidget,&tabContainer,convertToString(&widget)));
	
	buttonContainer.autoSize();
	
	buttons.push_back(button);
	
	tabContainer.addWidget(convertToString(&widget),widget);
	widget.setVisible(false);
	
	buttonContainer.addWidget(*button);
}
