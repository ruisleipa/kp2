#include "updater.hpp"
#include <QDebug>

Updater::Updater(MusicPlayer& musicPlayer, Connection& connection, QObject *parent) :
	QObject(parent),
	musicPlayer(musicPlayer),
	connection(connection)
{
	
}

Updater::~Updater()
{

}

void Updater::update()
{
	musicPlayer.update();
	connection.processPackets();
}
