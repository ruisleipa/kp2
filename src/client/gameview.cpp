#include "gameview.hpp"

#include <sstream>

MenuContainer* GameView::getContainer()
{
	return ui->menuContainer;
}

void GameView::gameStateLoaded(Client::State* state)
{
	player = state->getPlayer();
	
	connect(player, SIGNAL(changed()), this, SLOT(update()));
	
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
	
	ui->infoLabel->setText(s.str().c_str());
}

GameView::GameView(QWidget *parent) :
	Menu(parent),
	ui(new Ui::GameView),
	player(nullptr)
{
	ui->setupUi(this);
}

