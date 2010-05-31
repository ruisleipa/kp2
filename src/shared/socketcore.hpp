#ifndef __SOCKETCORE_HPP
#define __SOCKETCORE_HPP

#include <string>

class SocketCore
{
	public:
		static SocketCore& getInstance();

		std::string getErrorMessage();
		
		~SocketCore();

	private:
		SocketCore();
};

#endif // __SOCKETCORE_HPP
