#ifndef MENU_H
#define MENU_H

#include <QWidget>

namespace Client
{

class Menu: public QWidget
{
	Q_OBJECT

	public:
		explicit Menu(QWidget *parent = 0);

	protected:
		void paintEvent(QPaintEvent *);

	signals:
		void navigateTo(const QString& name);
		void navigateToPrevious();
};

}

#endif
