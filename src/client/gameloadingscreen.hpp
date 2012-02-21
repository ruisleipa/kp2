#ifndef CLIENT_GAMELOADINGSCREEN_HPP
#define CLIENT_GAMELOADINGSCREEN_HPP

#include <memory>

#include "state.hpp"
#include "menu.hpp"
#include "ui_gameloadingscreen.h"

class MenuContainer;

class GameLoadingScreen : public Menu
{	
	Q_OBJECT

public:
	explicit GameLoadingScreen(QWidget *parent = 0);

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
	
private:
	std::unique_ptr<Ui::GameLoadingScreen> ui;
	
private slots:
	void on_cancelButton_clicked();

};

#endif
