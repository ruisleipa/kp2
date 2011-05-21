#include "musicplayer.hpp"

#include <cstdlib>
#include <ctime>
#include <iostream>
#include <algorithm>

#include "utils/directory.hpp"

void MusicPlayer::update()
{
	if(volume == 0 || (sound && sound->isPlaying()))
		return;

	play(pick());
}

void MusicPlayer::playRandomSong()
{
	play(pick());
}

void MusicPlayer::setVolume(int volume)
{
	if(volume > 100)
		volume = 100;
	
	if(this->volume == 0 && volume > 0)
	{
		playRandomSong();		
	}
	
	if(volume == 0)
	{
		sound = 0;
	}
	
	if(sound)
		sound->setVolume(volume / 100.0);
		
	this->volume = volume;
}

int MusicPlayer::getVolume()
{
	return volume;
}

MusicPlayer::MusicPlayer():
	device(0),
	sound(0),
	currentSong(0),
	volume(100)
{
	loadSettings();

	files = readDirectory(MUSIC_DIRECTORY);
	
	srand(time(NULL));
	
	std::random_shuffle(files.begin(), files.end());
	
	device = audiere::OpenDevice();
}

MusicPlayer::~MusicPlayer()
{
	try
	{
		saveSettings();
	}
	catch(...)
	{
		
	}
}

std::string MusicPlayer::pick()
{
	currentSong = currentSong % files.size();
	
	if(currentSong >= files.size())
		return "";
	
	return files[currentSong++];
}

void MusicPlayer::play(const std::string& file)
{
	if(!device)
		return;

	sound = audiere::OpenSound(device, (MUSIC_DIRECTORY + file).c_str());

	sound->setVolume(volume / 100.0);
	sound->play();
}

void MusicPlayer::loadSettings()
{
	settings.load(MUSIC_SETTINGS);
	
	settings.getValue("volume", volume);
}

void MusicPlayer::saveSettings()
{
	settings.setValue("volume", volume);
	
	settings.save(MUSIC_SETTINGS);
}
