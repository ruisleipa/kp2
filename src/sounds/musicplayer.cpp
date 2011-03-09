#include "musicplayer.hpp"

#include <cstdlib>
#include <iostream>
#include <algorithm>

#include "utils/directory.hpp"

void MusicPlayer::update()
{
	if(sound && sound->isPlaying())
		return;

	play(pick());
}

void MusicPlayer::playRandomSong()
{
	play(pick());
}

MusicPlayer::MusicPlayer():
	device(0),
	sound(0),
	currentSong(0),
	volume(1.0)
{
	loadSettings();

	files = readDirectory(MUSIC_DIRECTORY);
	
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

	sound->setPitchShift(1.0);
	sound->setVolume(volume);
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
