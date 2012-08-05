#ifndef CLIENT_MAINWINDOW_H
#define CLIENT_MAINWINDOW_H

#include <memory>

#include <QMainWindow>

#include "ui_mainwindow.h"
#include "menucontainer.hpp"

namespace Client
{

class MainWindow : public QMainWindow
{
	Q_OBJECT

	public:
		void addMenu(Menu *menu);

		explicit MainWindow(QWidget *parent = 0);

	private:
		std::unique_ptr<Ui::MainWindow> ui;

};

}

#endif
