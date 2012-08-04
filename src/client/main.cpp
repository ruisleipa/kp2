#include <memory>
#include <QtGui/QApplication>
#include <QtGui/QStackedLayout>
#include <QString>
#include <QTextStream>
#include <QFile>
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

void loadStyleSheet(QApplication& app)
{
	QFile file("data/style/stylesheet.qss");
	file.open(QIODevice::ReadOnly);
	QString styleSheet = QTextStream(&file).readAll();
	file.close();

	app.setStyleSheet(styleSheet);
}

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

	QApplication::setStyle(new QWindowsStyle);

	QApplication a(argc, argv);

	MainWindow w;

	MusicPlayer musicPlayer;
	Connection connection;

	MainMenu* mainMenu = new MainMenu();
	SettingsMenu* settingsMenu = new SettingsMenu(musicPlayer);
	SinglePlayerMenu* singlePlayerMenu = new SinglePlayerMenu(connection);
	MultiPlayerMenu* multiPlayerMenu = new MultiPlayerMenu(connection);
	GameLoadingScreen* gameLoadingScreen = new GameLoadingScreen();
	GameView* gameView = new GameView();

	QObject::connect(gameLoadingScreen, SIGNAL(cancelled()), &connection, SLOT(close()));
	QObject::connect(&connection, SIGNAL(startingLocalServer()), gameLoadingScreen, SLOT(onStartingLocalServer()));
	QObject::connect(&connection, SIGNAL(connectingToRemote()), gameLoadingScreen, SLOT(onConnectingToRemote()));
	QObject::connect(&connection, SIGNAL(connectingToLocal()), gameLoadingScreen, SLOT(onConnectingToLocal()));
	QObject::connect(&connection, SIGNAL(connected()), gameLoadingScreen, SLOT(onConnected()));
	QObject::connect(&connection, SIGNAL(receivingGameState()), gameLoadingScreen, SLOT(onReceivingGameState()));
	QObject::connect(&connection, SIGNAL(error(const std::string&)), gameLoadingScreen, SLOT(onError(const std::string&)));

	QObject::connect(&connection, SIGNAL(ready(Client::State*)), gameLoadingScreen, SLOT(onCompletion(Client::State*)));
	QObject::connect(&connection, SIGNAL(ready(Client::State*)), gameView, SLOT(gameStateLoaded(Client::State*)));

	mainWindow.addMenu(mainMenu);
	mainWindow.addMenu(settingsMenu);
	mainWindow.addMenu(singlePlayerMenu);
	mainWindow.addMenu(multiPlayerMenu);
	mainWindow.addMenu(gameLoadingScreen);
	mainWindow.addMenu(gameView);

	GameMainMenu* gameMainMenu = new GameMainMenu();
	CarShopMenu* carShopMenu = new CarShopMenu();
	GarageMenu* garageMenu = new GarageMenu();

	QObject::connect(&connection, SIGNAL(ready(Client::State*)), gameMainMenu, SLOT(gameStateLoaded(Client::State*)));
	QObject::connect(&connection, SIGNAL(ready(Client::State*)), carShopMenu, SLOT(gameStateLoaded(Client::State*)));
	QObject::connect(&connection, SIGNAL(ready(Client::State*)), garageMenu, SLOT(gameStateLoaded(Client::State*)));

	gameView->addMenu(gameMainMenu);
	gameView->addMenu(carShopMenu);
	gameView->addMenu(garageMenu);

	Updater updater(musicPlayer, connection);
	loadStyleSheet(a);

	QTimer updateTimer;
	QObject::connect(&updateTimer, SIGNAL(timeout()), &updater, SLOT(update()));

	updateTimer.start(500);

	qInstallMsgHandler(customMessageHandler);

	w.show();
	w.dumpObjectTree();

	return a.exec();
}
