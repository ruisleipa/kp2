#include "mainwindow.hpp"

void MainWindow::addMenu(Menu* menu)
{
	ui->menuContainer->addMenu(menu);
}

MainWindow::MainWindow(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::MainWindow)
{
	ui->setupUi(this);
}



