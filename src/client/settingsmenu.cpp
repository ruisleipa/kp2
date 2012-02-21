#include "settingsmenu.hpp"
#include "ui_settingsmenu.h"

SettingsMenu::SettingsMenu(MusicPlayer& musicPlayer, QWidget *parent) :
	Menu(parent),
	ui(new Ui::SettingsMenu),
	musicPlayer(musicPlayer)
{
	ui->setupUi(this);
	
	ui->musicVolumeSlider->setValue(musicPlayer.getVolume());
}

SettingsMenu::~SettingsMenu()
{
	delete ui;
}

void SettingsMenu::on_pushButton_clicked()
{
	navigateToPrevious();
}

void SettingsMenu::on_musicVolumeSlider_valueChanged(int volume)
{
	musicPlayer.setVolume(volume);
}
