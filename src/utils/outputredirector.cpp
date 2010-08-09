#include "outputredirector.hpp"

OutputRedirector::OutputRedirector(const std::string& filename)
{
	m_filestream.open(filename.c_str(),std::ios_base::trunc);
	
	m_cout_buffer = std::cout.rdbuf();
	m_cerr_buffer = std::cerr.rdbuf();
	
	std::cout.rdbuf(m_filestream.rdbuf());
	std::cerr.rdbuf(m_filestream.rdbuf());
}

OutputRedirector::~OutputRedirector()
{
	std::cout.rdbuf(m_cout_buffer);
	std::cerr.rdbuf(m_cerr_buffer);
}
