#ifndef TECHNICSMENU_H
#define TECHNICSMENU_H

#include "gamemenu.hpp"

namespace Ui {
	class TechnicsMenu;
}

class TechnicsMenu : public GameMenu
{	Q_OBJECT

public:
	explicit TechnicsMenu(QWidget *parent = 0);
	~TechnicsMenu();

private:
	Ui::TechnicsMenu *ui;
	
private slots:
	void on_okButton_clicked();
	void on_cancelButton_clicked();

	
};

#endif // TECHNICSMENU_H
