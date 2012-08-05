#include "musicplayer.hpp"

#include <fstream>
#include <iostream>
#include <algorithm>
#include <ctime>
#include <cmath>

#include "utils/directory.hpp"
#include "json/json.h"

void MusicPlayer::update()
{
	if(volume == 0 || (sound && sound->isPlaying()))
		return;

	playRandomSong();
}

void MusicPlayer::playRandomSong()
{
	play(pick());
}

void MusicPlayer::setVolume(int volume)
{
	if(volume > 100)
		volume = 100;

	/*if(this->volume == 0 && volume > 0)
	{
		playRandomSong();
	}
	*/

	float coeff = volume / 100.0;

	if(sound)
	{
		sound->setVolume(coeff * coeff);
	}


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
	try
	{
		loadSettings();
	}
	catch(...)
	{

	}

	files = readDirectory(MUSIC_DIRECTORY);

	std::mt19937 rng;

	rng.seed(std::time(nullptr));

	std::shuffle(files.begin(), files.end(), rng);

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
	if(files.size() == 0)
		return "";

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

	if(!sound)
		return;

	setVolume(volume);
	sound->play();
}

void MusicPlayer::loadSettings()
{
	Json::Value settings;

	std::ifstream(MUSIC_SETTINGS) >> settings;

	volume = settings["volume"].asDouble();
}

void MusicPlayer::saveSettings()
{
	Json::Value settings;

	settings["volume"] = volume;

	std::ofstream(MUSIC_SETTINGS) << settings;
}
