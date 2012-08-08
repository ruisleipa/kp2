#ifndef CLIENT_MENUCONTAINER_H
#define CLIENT_MENUCONTAINER_H

#include <memory>
#include <stack>

#include <QWidget>

#include "menu.hpp"
#include "ui_menucontainer.h"

namespace Client
{

class MenuContainer : public QWidget, private Ui::MenuContainer
{
	Q_OBJECT

	public:
		void addMenu(Menu* menu);
		explicit MenuContainer(QWidget *parent = 0);

	public slots:
		void navigateTo(QString name);
		void navigateToPrevious();

	private:
		bool setVisibleMenu(QString name);

		std::stack<QString> navigationHistory;
};

}

#endif
