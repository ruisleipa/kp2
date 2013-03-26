#ifndef CLIENT_SETTINGSMENUFACTORY_HPP
#define CLIENT_SETTINGSMENUFACTORY_HPP

#include "settingsmenu.hpp"

class SettingsMenuFactory
{
	public:
		SettingsMenu* create();

		SettingsMenuFactory(MusicPlayer&);

	private:
		MusicPlayer& musicPlayer;
};

#endif
