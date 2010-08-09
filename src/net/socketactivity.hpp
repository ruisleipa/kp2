#ifndef SOCKETACTIVITY_HPP
#define SOCKETACTIVITY_HPP

class Socket;

class SocketActivity
{
	public:
		Socket* getSocket();
		bool canWrite();
		bool canRead();

		SocketActivity();
		SocketActivity(Socket* socket,bool can_read,bool can_write);

	private:
		Socket* m_socket;
		bool m_can_write;
		bool m_can_read;		
};

#endif // SOCKETACTIVITY_HPP

