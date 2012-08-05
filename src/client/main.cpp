#include "application.hpp"

#include <QWindowsStyle>
#include <QTimer>
#include "mainwindow.hpp"
#include "menu.hpp"
#include "updater.hpp"

#include "sounds/musicplayer.hpp"
#include "utils/outputredirector.hpp"

#include "mainmenu.hpp"
#include "settingsmenu.hpp"
#include "singleplayermenu.hpp"
#include "multiplayermenu.hpp"
#include "gameloadingscreen.hpp"
#include "gameview.hpp"
#include "connection.hpp"

#include "gamemainmenu.hpp"
#include "carshopmenu.hpp"
#include "garagemenu.hpp"


void customMessageHandler(QtMsgType type, const char *msg)
{
	QString txt;
	switch (type)
	{
		case QtDebugMsg:
			txt = QString("Debug: %1").arg(msg);
			break;
		case QtWarningMsg:
			txt = QString("Warning: %1").arg(msg);
			break;
		case QtCriticalMsg:
			txt = QString("Critical: %1").arg(msg);
			break;
		case QtFatalMsg:
			txt = QString("Fatal: %1").arg(msg);
			abort();
	}

	std::cout << txt.toStdString() << std::endl;
}

int main(int argc, char *argv[])
{
	OutputRedirector redirect("client.log");

	Client::Application application(argc, argv);

	Client::MainWindow mainWindow;

	MusicPlayer musicPlayer;
	Client::Connection connection;

	Client::MainMenu* mainMenu = new Client::MainMenu();
	Client::SettingsMenu* settingsMenu = new Client::SettingsMenu(musicPlayer);
	Client::SinglePlayerMenu* singlePlayerMenu = new Client::SinglePlayerMenu(connection);
	Client::MultiPlayerMenu* multiPlayerMenu = new Client::MultiPlayerMenu(connection);
	Client::GameLoadingScreen* gameLoadingScreen = new Client::GameLoadingScreen(connection);
	Client::GameView* gameView = new Client::GameView();

	QObject::connect(&connection, SIGNAL(ready(Client::State*)), gameView, SLOT(gameStateLoaded(Client::State*)));

	mainWindow.addMenu(mainMenu);
	mainWindow.addMenu(settingsMenu);
	mainWindow.addMenu(singlePlayerMenu);
	mainWindow.addMenu(multiPlayerMenu);
	mainWindow.addMenu(gameLoadingScreen);
	mainWindow.addMenu(gameView);

	Client::GameMainMenu* gameMainMenu = new Client::GameMainMenu();
	Client::CarShopMenu* carShopMenu = new Client::CarShopMenu();
	Client::GarageMenu* garageMenu = new Client::GarageMenu();

	QObject::connect(&connection, SIGNAL(ready(Client::State*)), gameMainMenu, SLOT(gameStateLoaded(Client::State*)));
	QObject::connect(&connection, SIGNAL(ready(Client::State*)), carShopMenu, SLOT(gameStateLoaded(Client::State*)));
	QObject::connect(&connection, SIGNAL(ready(Client::State*)), garageMenu, SLOT(gameStateLoaded(Client::State*)));

	gameView->addMenu(gameMainMenu);
	gameView->addMenu(carShopMenu);
	gameView->addMenu(garageMenu);

	Client::Updater updater(musicPlayer, connection);

	QTimer updateTimer;
	QObject::connect(&updateTimer, SIGNAL(timeout()), &updater, SLOT(update()));

	updateTimer.start(500);

	qInstallMsgHandler(customMessageHandler);

	mainWindow.show();
	mainWindow.dumpObjectTree();

	return application.exec();
}
