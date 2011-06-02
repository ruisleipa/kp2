#ifndef SOCKETACTIVITY_HPP
#define SOCKETACTIVITY_HPP

class Socket;

class SocketActivity
{
	public:
		Socket* socket;
		bool canWrite;
		bool canRead;
		bool timeoutExpired;
};

#endif // SOCKETACTIVITY_HPP

