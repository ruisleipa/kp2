#ifndef CLIENT_MAINWINDOW_H
#define CLIENT_MAINWINDOW_H

#include <memory>

#include <QMainWindow>

#include "ui_mainwindow.h"
#include "menucontainer.hpp"

class MainWindow : public QMainWindow
{
	Q_OBJECT

	public:
		MenuContainer* getContainer();
	
		explicit MainWindow(QWidget *parent = 0);

	private:
		std::unique_ptr<Ui::MainWindow> ui;

};

#endif
