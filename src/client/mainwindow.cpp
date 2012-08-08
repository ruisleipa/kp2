#include "mainwindow.hpp"

namespace Client
{

void MainWindow::addMenu(Menu* menu)
{
	menuContainer->addMenu(menu);
}

MainWindow::MainWindow(QWidget *parent) :
	QMainWindow(parent)
{
	setupUi(this);
}

}
