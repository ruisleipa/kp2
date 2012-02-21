#ifndef CLIENT_GAMEMENU_HPP
#define CLIENT_GAMEMENU_HPP

#include "menu.hpp"
#include "state.hpp"

class GameMenu: public Menu
{
	Q_OBJECT

	public:
		explicit GameMenu(QWidget *parent = 0);

	public slots:
		virtual void gameStateLoaded(Client::State*);
};

#endif
