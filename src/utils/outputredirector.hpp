#ifndef OUTPUTREDIRECTOR_HPP
#define OUTPUTREDIRECTOR_HPP

#include <iostream>
#include <fstream>

class OutputRedirector
{
	public:
		OutputRedirector(const std::string& filename);
		~OutputRedirector();

	private:
		std::ofstream m_filestream;
		std::streambuf* m_cout_buffer;
		std::streambuf* m_cerr_buffer;
};

#endif // OUTPUTREDIRECTOR_HPP

