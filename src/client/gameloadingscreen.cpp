#include "gameloadingscreen.hpp"

#include <iostream>

namespace Client
{

GameLoadingScreen::GameLoadingScreen(Connection& connection, QWidget *parent) :
	Menu(parent)
{
	setupUi(this);

	connect(this, SIGNAL(cancelled()), &connection, SLOT(close()));
	connect(&connection, SIGNAL(startingLocalServer()), this, SLOT(onStartingLocalServer()));
	connect(&connection, SIGNAL(connectingToRemote()), this, SLOT(onConnectingToRemote()));
	connect(&connection, SIGNAL(connectingToLocal()), this, SLOT(onConnectingToLocal()));
	connect(&connection, SIGNAL(connected()), this, SLOT(onConnected()));
	connect(&connection, SIGNAL(receivingGameState()), this, SLOT(onReceivingGameState()));
	connect(&connection, SIGNAL(error(const std::string&)), this, SLOT(onError(const std::string&)));
	connect(&connection, SIGNAL(ready(Client::State*)), this, SLOT(onCompletion(Client::State*)));
}

void GameLoadingScreen::onStartingLocalServer()
{
	progressLabel->setText(trUtf8("Käynnistetään yksinpelin palvelinta..."));
	progressBar->setValue(10);
}

void GameLoadingScreen::onConnectingToRemote()
{
	progressLabel->setText(trUtf8("Yhdistetään verkkopeliin..."));
	progressBar->setValue(25);
}

void GameLoadingScreen::onConnectingToLocal()
{
	progressLabel->setText(trUtf8("Yhdistetään paikalliseen peliin..."));
	progressBar->setValue(25);
}

void GameLoadingScreen::onConnected()
{
	progressLabel->setText(trUtf8("Yhdistetty..."));
	progressBar->setValue(40);
}

void GameLoadingScreen::onReceivingGameState()
{
	progressLabel->setText(trUtf8("Ladataan pelitilannetta..."));
	progressBar->setValue(60);
}

void GameLoadingScreen::onCompletion(Client::State* state)
{
	progressLabel->setText(trUtf8("Ladattu..."));
	progressBar->setValue(100);

	emit navigateTo("GameView");
}

void GameLoadingScreen::onError(const std::string& str)
{
	progressLabel->setText(trUtf8(str.c_str()));
	progressBar->setValue(100);
}

void GameLoadingScreen::on_cancelButton_clicked()
{
	emit navigateToPrevious();
	emit cancelled();
}

}
