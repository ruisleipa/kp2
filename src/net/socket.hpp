#ifndef SOCKET_HPP
#define SOCKET_HPP

#include <string>
#include <set>

class SocketSet;

class ConnectionClosedException
{

};

class Socket
{
	public:		
		void captureSocket(int socket);
		int releaseSocket();
		
		Socket();
		Socket(const Socket&);
		Socket& operator=(const Socket&);	
		
		virtual ~Socket();
		
	protected:
		bool connectImpl(const std::string& hostname,const int port);
		bool bindImpl(const std::string& hostname,const int port);
		
		bool acceptImpl(int& socket);
		
		int readImpl(char* data,int size);
		int writeImpl(const char* data,int size);
		
		mutable int m_socket;
		
	private:
		bool isWritePending();
		void commitWrite();
		
		bool setNonBlock(int socket);	

		void close();
	
		std::string getErrorMessage();		
		
		std::string m_write_buffer;
		
		std::set<SocketSet*> m_socket_sets;
		
		friend class SocketSet;
		
#ifdef WIN32			
		static int m_winsock_ref_count;
#endif
		
};

#endif // SOCKET_HPP

