#ifndef STACKTRACE_HPP
#define STACKTRACE_HPP

#include "stack.hpp"

class StackTrace
{
	public:
		void printStackTrace();
		
	private:
		void setPrintFormatting();
		void iterateAndPrintStack(const dbg::stack& stack);
		void printStackFrame(const dbg::stack_frame& stack_frame);
};

#endif // STACKTRACE_HPP
