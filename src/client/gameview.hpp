#ifndef CLIENT_GAMEVIEW_H
#define CLIENT_GAMEVIEW_H

#include <memory>

#include <QWidget>

#include "state.hpp"

#include "ui_gameview.h"

#include "menu.hpp"
#include "gamemenu.hpp"

namespace Client
{

class GameView : public Menu, public Game::Object::Listener, private Ui::GameView
{
	Q_OBJECT

	public:
		void addMenu(GameMenu *menu);
		void onChange(Game::Object* object);

		explicit GameView(QWidget *parent = 0);

	public slots:
		void gameStateLoaded(Client::State*);

	private:
		Game::Player* player;

	private slots:
		void on_settingsButton_clicked();
		void update();
};

}

#endif
