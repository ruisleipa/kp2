#ifndef CLIENT_CONNECTION_HPP
#define CLIENT_CONNECTION_HPP

#include <QObject>
#include <string>
#include <QProcess>
#include <QTcpSocket>

#include "net/packet.hpp"
#include "state.hpp"
#include "clientobjectfactory.hpp"

class Packet;

const int BUFFERSIZE=512;

class Connection : public QObject
{
	Q_OBJECT

	public:
		void connect(std::string hostname,int port);
		void startLocalServer();

		void processPackets();

		Game::State& getGameState();

		void writeToServer(const Net::Packet& packet);

		Connection();
		~Connection();

	public slots:
		void close();

	signals:
		void startingLocalServer();
		void connectingToRemote();
		void connectingToLocal();
		void connected();
		void receivingGameState();
		void ready(Client::State* state);
		void error(const std::string& error);

	private:
		QTcpSocket socket;

		std::string receiveBuffer;
		char scrapBuffer[BUFFERSIZE];

		QProcess serverProcess;

		ClientObjectFactory objectFactory;

		std::unique_ptr<Client::State> state;

	private slots:
		void onServerError(QProcess::ProcessError);
		void onServerStarted();
		void onConnected();
};

#endif

