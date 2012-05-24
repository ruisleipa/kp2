#include "mainwindow.hpp"

#include <QtGui/QApplication>
#include <QFileDialog>
#include <fstream>
#include <iostream>

MainWindow::MainWindow(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::MainWindow)
{
	ui->setupUi(this);

	ui->saveAction->setEnabled(false);
	ui->saveAsAction->setEnabled(false);
	ui->closeAction->setEnabled(false);
}

void MainWindow::on_newAction_triggered()
{

}

void MainWindow::on_openAction_triggered()
{
	fileName = QFileDialog::getOpenFileName(this, tr("Avaa..."), "", tr("KP2 SE-tallennukset (*.kp2)")).toStdString();

	if(fileName == "")
		return;

	Json::Value stateJson;

	std::ifstream(fileName) >> stateJson;

	Game::ObjectFactory factory;

	state.reset(new Game::State(stateJson, factory));

	ui->saveAction->setEnabled(true);
	ui->saveAsAction->setEnabled(true);
	ui->closeAction->setEnabled(true);
}

void MainWindow::on_saveAction_triggered()
{
	if(fileName == "")
	{
		on_saveAsAction_triggered();
		return;
	}

	Json::Value stateJson;

	state->save(stateJson);

	std::ofstream(fileName) << stateJson;
}

void MainWindow::on_saveAsAction_triggered()
{
	std::string fileName = QFileDialog::getSaveFileName(this, tr("Tallenna nimellä..."), "", tr("KP2 SE-tallennukset (*.kp2)")).toStdString();

	if(fileName == "")
		return;

	this->fileName = fileName;

	Json::Value stateJson;

	state->save(stateJson);

	std::ofstream(fileName) << stateJson;
}

void MainWindow::on_closeAction_triggered()
{
	state.reset(0);

	ui->saveAction->setEnabled(false);
	ui->saveAsAction->setEnabled(false);
	ui->closeAction->setEnabled(false);
}

void MainWindow::on_quitAction_triggered()
{
	QApplication::exit(0);
}
