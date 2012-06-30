#ifndef EDITOR_TIREFORM_HPP
#define EDITOR_TIREFORM_HPP

#include <memory>

#include <QWidget>

#include "ui_tireform.h"
#include "game/tire.hpp"

class TireForm : public QWidget
{
	Q_OBJECT

	public:
		explicit TireForm(Game::Tire* tire, QWidget *parent = 0);

	private:
		Game::Tire generate();
	
		std::unique_ptr<Ui::TireForm> ui;
		
		Game::Tire* tire;	
		
	private slots:
		void on_closeButton_clicked();
		void on_saveButton_clicked();
		void on_okButton_clicked();
	
};

#endif
