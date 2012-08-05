#include "menucontainer.hpp"

#include <iostream>

void MenuContainer::addMenu(Menu* menu)
{
	if(ui->container->count() == 0)
	{
		std::cout << "pushing first " << menu->objectName().toStdString() << std::endl;

		navigationHistory.push(menu->objectName());
	}

	ui->container->addWidget(menu);

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
	QWidget* widget = ui->container->findChild<QWidget*>(name);

	if(!widget)
		return false;

	ui->container->setCurrentWidget(widget);

	return true;
}

MenuContainer::MenuContainer(QWidget *parent) :
	QWidget(parent),
	ui(new Ui::MenuContainer)
{
	ui->setupUi(this);
}
