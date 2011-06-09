#include "tabbedmenu.hpp"

#include "utils/string.hpp"

TabbedMenu::TabbedMenu()
{
	addWidget(topContainer, "0px", "0px", "100%", "100%");
	
	topContainer.addWidget(buttonContainer, "100%", "auto");
	topContainer.addWidget(tabContainer, "100%", "1~");
	
	tabContainer.setBackgroundColor(Color(1,1,1,0.5));
	
	buttonContainer.showOuterPadding(false);
}

void TabbedMenu::addTab(const std::string& label,Widget& widget)
{
	std::tr1::shared_ptr<Button> button(new Button);
	
	button->setText(label);
	button->setClickHandler(std::tr1::bind(&Container::showOnlyWidget,&tabContainer,convertToString(&widget)));
	
	buttons.push_back(button);
	
	buttonContainer.addWidget(*button, "auto", "auto");
	
	tabContainer.addWidget(widget, "0px", "0px", "100%", "100%");
	widget.setName(convertToString(&widget));
	widget.setVisible(false);
	
	
}
