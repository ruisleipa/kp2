#ifndef SETTINGSMENU_H
#define SETTINGSMENU_H

#include "sounds/musicplayer.hpp"
#include "menu.hpp"
#include "ui_settingsmenu.h"

namespace Client
{

class SettingsMenu : public Menu, private Ui::SettingsMenu
{
	Q_OBJECT

public:
	explicit SettingsMenu(MusicPlayer& musicPlayer, QWidget *parent = 0);

private:
	MusicPlayer& musicPlayer;

private slots:
	void on_pushButton_clicked();
	void on_musicVolumeSlider_valueChanged(int);
};

}

#endif // SETTINGSMENU_H
