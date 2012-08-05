#include "updater.hpp"
#include <QDebug>

namespace Client
{

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

}
