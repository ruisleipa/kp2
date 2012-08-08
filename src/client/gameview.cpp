#include "gameview.hpp"

#include <sstream>

namespace Client
{

void GameView::addMenu(GameMenu* menu)
{
	menuContainer->addMenu(menu);
}

void GameView::onChange(Game::Object* object)
{
	update();
}

void GameView::gameStateLoaded(Client::State* state)
{
	player = state->getPlayer();

	player->addListener(this);

	update();
}

void GameView::on_settingsButton_clicked()
{
	emit navigateTo("SettingsMenu");
}

void GameView::update()
{
	std::stringstream s;

	s << player->getName() << ", ";
	s << player->getMoney();

	infoLabel->setText(s.str().c_str());
}

GameView::GameView(QWidget *parent) :
	Menu(parent),
	player(nullptr)
{
	setupUi(this);
}

}

