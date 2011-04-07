#include "crashcatcher.hpp"

#include <csignal>
#include <cstdlib>
#include <iostream>

#include "stacktrace.hpp"
#include "crashmessage.hpp"
#include "stack.hpp"

CrashCatcher* CrashCatcher::catcher = 0;

CrashCatcher::CrashCatcher(CrashMessage& crash_message):
	crashMessage(crash_message)
{
	installCatcher();
}

CrashCatcher::~CrashCatcher()
{
	uninstallCatcher();
}

void CrashCatcher::installCatcher()
{
#ifdef WIN32
	exceptionRegistration.object = this;
	exceptionRegistration.handler = reinterpret_cast<PEXCEPTION_HANDLER>(&CrashCatcher::catchCrash);
	asm volatile("movl %%fs:0, %0" : "=r" (exceptionRegistration.prev));
	asm volatile("movl %0, %%fs:0" : : "r" (&exceptionRegistration));
#else	
	std::signal(SIGSEGV, &CrashCatcher::catchCrash);
	std::signal(SIGFPE, &CrashCatcher::catchCrash);

	catcher = this;
#endif
}

void CrashCatcher::uninstallCatcher()
{
#ifdef WIN32
	asm volatile("movl %0, %%fs:0" : : "r" (exceptionRegistration.prev));
#else	
	std::signal(SIGSEGV, SIG_DFL);
	std::signal(SIGFPE, SIG_DFL);
#endif
}

#ifdef WIN32
LONG CrashCatcher::catchCrash(PEXCEPTION_RECORD, EXCEPTION_REGISTRATION* registration, PCONTEXT, PEXCEPTION_RECORD)
#else
void CrashCatcher::catchCrash(int signal_number)
#endif
{
#ifdef WIN32
	ExceptionRegistration* exceptionRegistration = reinterpret_cast<ExceptionRegistration*>(registration);

	exceptionRegistration->object->handleCrash();
#else	
	catcher->handleCrash();
#endif
	
#ifdef WIN32
	return 0;
#endif
}

void CrashCatcher::handleCrash()
{
	uninstallCatcher();
	printStackTrace();
	showMessage();
	std::exit(1);
}

void CrashCatcher::printStackTrace()
{
	printStackTraceHeader();

	StackTrace stack_trace;	
	stack_trace.printStackTrace();
}

void CrashCatcher::showMessage()
{
	crashMessage.showMessage();
}

void CrashCatcher::printStackTraceHeader()
{
	std::cout << "---Stack trace---" << std::endl;
}
