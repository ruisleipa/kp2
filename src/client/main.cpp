#include "application.hpp"
#include "shared/outputredirector.hpp"

#ifdef WIN32

#include <windows.h>
#include <io.h>
#include <fcntl.h>

void ActivateConsole()
{
	AllocConsole();

	HANDLE newConsoleInput = GetStdHandle(STD_INPUT_HANDLE);
	HANDLE newConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	HANDLE newConsoleError = GetStdHandle(STD_ERROR_HANDLE);

	int inFd = _open_osfhandle((long)newConsoleInput, _O_TEXT);
	int outFd = _open_osfhandle((long)newConsoleOutput, _O_TEXT);
	int errorFd = _open_osfhandle((long)newConsoleError, _O_TEXT);

	FILE* consoleIn = _fdopen(inFd, "r");
	FILE* consoleOut = _fdopen(outFd, "w");
	FILE* consoleError = _fdopen(errorFd, "w");

	setvbuf(consoleIn, NULL, _IONBF, 0);
	setvbuf(consoleOut, NULL, _IONBF, 0);
	setvbuf(consoleError, NULL, _IONBF, 0);

	*stdin = *consoleIn;
	*stdout = *consoleOut;
	*stderr = *consoleError;
}

#endif

#include <dlfcn.h>
#include <cxxabi.h>
#include <iostream>
#include <string>
#include <cstdlib>
#include <cstring>
#include <cxxabi.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

std::string demangle(const char *name)
{
    int status = 0;
    char *d = 0;
    std::string ret = name;
    try { if ( (d = abi::__cxa_demangle(name, 0, 0, &status)) ) ret = d; }
    catch(...) {  }
    std::free(d);
    return ret;
}

void trace()
{
    Dl_info info;
    void **frame = static_cast<void **>(__builtin_frame_address(0));
    void **bp = static_cast<void **>(*frame);
    void *ip = frame[1];

    while(bp && ip && dladdr(ip, &info))
    {
        std::cout << ip << ": " <<  demangle(info.dli_sname) << " in " << info.dli_fname << '\\n';

        if(info.dli_sname && !strcmp(info.dli_sname, "main")) break;

        ip = bp[1];
        bp = static_cast<void**>(bp[0]);
    }
}

void signal_handler(int sig)
{
	trace();
}

int main(int argc,char** argv)
{
	signal(SIGSEGV,signal_handler);
	
	OutputRedirector redirect("client.log");

#ifdef WIN32
	//ActivateConsole();
#endif
	Application application;	

	application.enterMainLoop();
}

