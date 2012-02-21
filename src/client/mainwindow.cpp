#include "mainwindow.hpp"

MenuContainer* MainWindow::getContainer()
{
	return ui->menuContainer;
}

MainWindow::MainWindow(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::MainWindow)
{
	ui->setupUi(this);
}
