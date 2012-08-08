#include "settingsmenu.hpp"

namespace Client
{

SettingsMenu::SettingsMenu(MusicPlayer& musicPlayer, QWidget *parent) :
	Menu(parent),
	musicPlayer(musicPlayer)
{
	setupUi(this);

	musicVolumeSlider->setValue(musicPlayer.getVolume());
}

void SettingsMenu::on_pushButton_clicked()
{
	navigateToPrevious();
}

void SettingsMenu::on_musicVolumeSlider_valueChanged(int volume)
{
	musicPlayer.setVolume(volume);
}

}
