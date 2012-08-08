#ifndef UPDATER_H
#define UPDATER_H

#include <QObject>

#include "sounds/musicplayer.hpp"
#include "connection.hpp"

namespace Client
{

class Updater : public QObject
{
	Q_OBJECT

	public:
		explicit Updater(MusicPlayer& musicPlayer, Connection& connection, QObject *parent = 0);
		~Updater();

	public slots:
		void update();

	private:
		MusicPlayer& musicPlayer;
		Connection& connection;
};

}

#endif
