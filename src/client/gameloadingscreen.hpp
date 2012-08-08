#ifndef CLIENT_GAMELOADINGSCREEN_HPP
#define CLIENT_GAMELOADINGSCREEN_HPP

#include <memory>

#include "state.hpp"
#include "menu.hpp"
#include "ui_gameloadingscreen.h"
#include "connection.hpp"

class MenuContainer;

namespace Client
{

class GameLoadingScreen : public Menu, private Ui::GameLoadingScreen
{
	Q_OBJECT

public:
	GameLoadingScreen(Connection& connection, QWidget *parent = 0);

public slots:
	void onStartingLocalServer();
	void onConnectingToRemote();
	void onConnectingToLocal();
	void onConnected();
	void onReceivingGameState();
	void onCompletion(Client::State*);
	void onError(const std::string&);

signals:
	void cancelled();

private slots:
	void on_cancelButton_clicked();

};

}

#endif
