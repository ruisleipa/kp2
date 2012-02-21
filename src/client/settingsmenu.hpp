#ifndef SETTINGSMENU_H
#define SETTINGSMENU_H

#include "sounds/musicplayer.hpp"
#include "menu.hpp"

namespace Ui {
	class SettingsMenu;
}

class SettingsMenu : public Menu
{
	Q_OBJECT

public:
	explicit SettingsMenu(MusicPlayer& musicPlayer, QWidget *parent = 0);
	~SettingsMenu();

private:
	Ui::SettingsMenu *ui;
	
	MusicPlayer& musicPlayer;

private slots:
	void on_pushButton_clicked();
	void on_musicVolumeSlider_valueChanged(int);
};

#endif // SETTINGSMENU_H
