#ifndef CLIENT_GAMEVIEW_H
#define CLIENT_GAMEVIEW_H

#include <memory>

#include <QWidget>

#include "state.hpp"

#include "ui_gameview.h"

#include "menu.hpp"

class GameView : public Menu, public Game::Object::Listener
{
	Q_OBJECT

	public:
		MenuContainer* getContainer();
		
		void onChange(Game::Object* object);

		explicit GameView(QWidget *parent = 0);
	
	public slots:
		void gameStateLoaded(Client::State*);
	
	private:
		std::unique_ptr<Ui::GameView> ui;
		
		Game::Player* player;
	
	private slots:
		void on_settingsButton_clicked();
		void update();
};

#endif
