#ifndef MUSICPLAYER_HPP
#define MUSICPLAYER_HPP

#include <cstring>
#include <string>
#include <audiere/audiere.h>

#include "utils/inifile.hpp"

const std::string MUSIC_DIRECTORY = "data/music/";
const std::string MUSIC_SETTINGS = "cfg/music.cfg";

class MusicPlayer
{
	public:				
		void update();
		void playRandomSong();
		
		void setVolume(float volume);
		void getVolume();
		
		MusicPlayer();
		~MusicPlayer();
	
	private:		
		std::vector<std::string> files;
		audiere::AudioDevicePtr device;
		audiere::OutputStreamPtr sound;
		size_t currentSong;
		float volume;
		
		IniFile settings;
		
		std::string pick();
		void play(const std::string& file);
		
		void loadSettings();
		void saveSettings();
};

#endif
