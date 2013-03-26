#include "settingsmenufactory.hpp"

SettingsMenu* SettingsMenuFactory::create()
{
	return new SettingsMenu(musicPlayer);
}

SettingsMenuFactory::SettingsMenuFactory(MusicPlayer& musicPlayer):
	musicPlayer(musicPlayer)
{

}
