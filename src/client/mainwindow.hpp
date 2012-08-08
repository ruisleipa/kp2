#ifndef CLIENT_MAINWINDOW_H
#define CLIENT_MAINWINDOW_H

#include <memory>

#include <QMainWindow>

#include "ui_mainwindow.h"
#include "menucontainer.hpp"

namespace Client
{

class MainWindow : public QMainWindow, private Ui::MainWindow
{
	Q_OBJECT

	public:
		void addMenu(Menu *menu);

		explicit MainWindow(QWidget *parent = 0);
};

}

#endif
