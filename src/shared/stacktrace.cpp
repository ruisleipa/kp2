#include "stacktrace.hpp"

#include <iostream>
#include <stdexcept>
#include <iomanip>

void StackTrace::printStackTrace()
{
	try
	{	
		dbg::stack stack;

		setPrintFormatting();
		iterateAndPrintStack(stack);
	}
	catch(std::runtime_error e)
	{
		std::cerr << "Cannot get stack trace:" << e.what() << std::endl;
	}
	catch(...)
	{
		std::cerr << "Cannot get stack trace." << std::endl;
	}
}

void StackTrace::setPrintFormatting()
{
	std::cout << std::hex;
	std::cout << std::setw(16);
	std::cout.fill('0');
}

void StackTrace::iterateAndPrintStack(const dbg::stack& stack)
{
	dbg::stack::const_iterator i;	
	
	for(i = stack.begin(); i != stack.end(); ++i)
		printStackFrame(*i);
}

void StackTrace::printStackFrame(const dbg::stack_frame& stack_frame)
{
	std::cout << stack_frame.module << ": ";
	std::cout << stack_frame.instruction << " ";
	std::cout << stack_frame.function << " ";
	std::cout << std::endl;
}
