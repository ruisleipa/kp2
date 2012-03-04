#ifndef TECHNICSMENU_H
#define TECHNICSMENU_H

#include <memory>

#include "gamemenu.hpp"
#include "ui_technicsmenu.h"
#include "parttablemodel.hpp"

class TechnicsMenu : public GameMenu
{	
	Q_OBJECT

	public:
		explicit TechnicsMenu(QWidget *parent = 0);

	public slots:
		virtual void gameStateLoaded(Client::State*);
		
	private:
		std::unique_ptr<Ui::TechnicsMenu> ui;
		std::unique_ptr<PartTableModel> model;
		
	private slots:
		void on_okButton_clicked();
		void on_cancelButton_clicked();

	
};

#endif // TECHNICSMENU_H
