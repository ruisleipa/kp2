#include "menucontainer.hpp"

#include <iostream>

namespace Client
{

void MenuContainer::addMenu(Menu* menu)
{
	if(container->count() == 0)
	{
		std::cout << "pushing first " << menu->objectName().toStdString() << std::endl;

		navigationHistory.push(menu->objectName());
	}

	container->addWidget(menu);

	QObject::connect(menu, SIGNAL(navigateTo(QString)), this, SLOT(navigateTo(QString)));
	QObject::connect(menu, SIGNAL(navigateToPrevious()), this, SLOT(navigateToPrevious()));
}

void MenuContainer::navigateTo(QString name)
{
	if(setVisibleMenu(name))
		navigationHistory.push(name);
}

void MenuContainer::navigateToPrevious()
{
	if(navigationHistory.size() > 1)
	{
		navigationHistory.pop();

		QString name = navigationHistory.top();

		setVisibleMenu(name);
	}
}

bool MenuContainer::setVisibleMenu(QString name)
{
	QWidget* widget = container->findChild<QWidget*>(name);

	if(!widget)
		return false;

	container->setCurrentWidget(widget);

	return true;
}

MenuContainer::MenuContainer(QWidget *parent) :
	QWidget(parent)
{
	setupUi(this);
}

}
