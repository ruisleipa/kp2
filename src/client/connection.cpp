#include "connection.hpp"

#include <iostream>
#include <fstream>
#include <stdint.h>
#include <cstdlib>
#include <stdexcept>
#include <QDebug>

#include "json/json.h"
#include "utils/string.hpp"
#include "net/packet.hpp"
#include "net/clientsocket.hpp"

void Connection::connect(std::string hostname,int port)
{
	socket.connectToHost(hostname.c_str(), port);
}

void Connection::close()
{
	socket.close();

	serverProcess.waitForFinished();


}

void Connection::processPackets()
{	
	if(socket.state() != QTcpSocket::ConnectedState)
		return;
	
	int read;

	while((read = socket.read(scrapBuffer, BUFFERSIZE)) > 0)
		receiveBuffer.append(scrapBuffer, read);

	if(read == -1)
		close();
	
	while(1)
	{
		Net::Packet packet;
	
		try
		{			
			packet.readFromBuffer(receiveBuffer);
			
			if(packet.getType() == 0)
			{
				emit receivingGameState();
			
				std::string s;
				
				packet >> s;

				std::stringstream ss(s);

				Json::Value v;

				ss >> v;

				std::cout << v;

				try
				{
					Client::State* state = new Client::State(v);

					emit ready(state);
				}
				catch(std::runtime_error& e)
				{
					emit error(e.what());
				}
			}
		}
		catch(Net::EndOfDataException)
		{
			/*
			We don't have enough data for a packet, so we return.
			*/
			return;
		}

	}
}

//TODO: implement correct sending (remote call api)
void Connection::writeToServer(const Net::Packet& packet)
{
	std::string str = packet.getString();

	socket.write(str.c_str(), str.size());
}

void Connection::startLocalServer()
{
	emit startingLocalServer();
	
	Json::Value settings;
	
	settings["port"] = 31000;
	settings["isLocal"] = true;
	settings["quitWhenEmpty"] = true;
	settings["connectionLimit"] = 1;
	
	std::ofstream("cfg/singleplayer.cfg") << settings;

	QString name = "kp2_server";
	QStringList args;
	args << "-config" << "cfg/singleplayer.cfg";
	
	serverProcess.start("./kp2_server", args);
}

void Connection::onServerError(QProcess::ProcessError error)
{
	std::cout << error << std::endl;
}

void Connection::onServerStarted()
{
	emit connectingToLocal();
		
	socket.connectToHost("localhost",31000);
}

void Connection::onConnected()
{
	emit connected();
}	

Connection::Connection()
{
	QObject::connect(&serverProcess, SIGNAL(started()), this, SLOT(onServerStarted()));
	QObject::connect(&serverProcess, SIGNAL(error(QProcess::ProcessError)), this, SLOT(onServerError(QProcess::ProcessError)));
	QObject::connect(&socket, SIGNAL(connected()), this, SLOT(onConnected()));
}

Connection::~Connection()
{
	socket.close();
	
	serverProcess.waitForFinished();
}		
