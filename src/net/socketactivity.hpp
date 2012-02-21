#ifndef NET_SOCKETACTIVITY_HPP
#define NET_SOCKETACTIVITY_HPP

namespace Net
{

class Socket;

class SocketActivity
{
	public:
		Socket* socket;
		bool canWrite;
		bool canRead;
		bool timeoutExpired;
};

};

#endif
