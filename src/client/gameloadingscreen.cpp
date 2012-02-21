#include "gameloadingscreen.hpp"

#include <iostream>

GameLoadingScreen::GameLoadingScreen(QWidget *parent) :
	Menu(parent),
	ui(new Ui::GameLoadingScreen)
{
	ui->setupUi(this);
}

void GameLoadingScreen::onStartingLocalServer()
{
	ui->progressLabel->setText(trUtf8("Käynnistetään yksinpelin palvelinta..."));
	ui->progressBar->setValue(10);
}

void GameLoadingScreen::onConnectingToRemote()
{
	ui->progressLabel->setText(trUtf8("Yhdistetään verkkopeliin..."));
	ui->progressBar->setValue(25);
}

void GameLoadingScreen::onConnectingToLocal()
{
	ui->progressLabel->setText(trUtf8("Yhdistetään paikalliseen peliin..."));
	ui->progressBar->setValue(25);
}

void GameLoadingScreen::onConnected()
{
	ui->progressLabel->setText(trUtf8("Yhdistetty..."));
	ui->progressBar->setValue(40);
}

void GameLoadingScreen::onReceivingGameState()
{
	ui->progressLabel->setText(trUtf8("Ladataan pelitilannetta..."));
	ui->progressBar->setValue(60);
}

void GameLoadingScreen::onCompletion(Client::State* state)
{
	ui->progressLabel->setText(trUtf8("Ladattu..."));
	ui->progressBar->setValue(100);
	
	emit navigateTo("GameView");
}

void GameLoadingScreen::onError(const std::string& str)
{
	ui->progressLabel->setText(trUtf8(str.c_str()));
	ui->progressBar->setValue(100);
}

void GameLoadingScreen::on_cancelButton_clicked()
{
	emit navigateToPrevious();	
	emit cancelled();
}
