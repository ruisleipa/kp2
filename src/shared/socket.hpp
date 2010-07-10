#ifndef __SOCKET_HPP
#define __SOCKET_HPP

#include <string>
#include <set>

class SocketSet;

class Socket
{
	public:		
		void captureSocket(int socket);
		int releaseSocket();
		
		Socket();
		
		virtual ~Socket();
		
	protected:
		bool connectImpl(const std::string& hostname,const int port);
		bool bindImpl(const std::string& hostname,const int port);
		
		bool acceptImpl(int& socket);
		
		int readImpl(char* data,int size);
		int writeImpl(const char* data,int size);
		
		mutable int m_socket;
		
	private:
		Socket(const Socket&);
		Socket& operator=(const Socket&);	
	
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

#endif // __SOCKET_HPP

