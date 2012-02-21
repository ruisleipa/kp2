#ifndef CLIENT_CONNECTION_HPP
#define CLIENT_CONNECTION_HPP

#include <QObject>
#include <string>
#include <QProcess>
#include <QTcpSocket>

#include "net/packet.hpp"
#include "utils/map.hpp"
#include "state.hpp"

class Packet;

const int BUFFERSIZE=512;

class Connection : public QObject
{
	Q_OBJECT

	public:				
		void connect(std::string hostname,int port);
		void startLocalServer();
		
		void processPackets();
		
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
		void writeToServer(const Net::Packet& packet);
		
		QTcpSocket socket;
		
		std::string receiveBuffer;
		char scrapBuffer[BUFFERSIZE];
		
		QProcess serverProcess;
		
	private slots:
		void onServerError(QProcess::ProcessError);
		void onServerStarted();
		void onConnected();
};

#endif

