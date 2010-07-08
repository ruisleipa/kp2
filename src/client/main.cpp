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

int main(int argc,char** argv)
{
	OutputRedirector redirect("client.log");

#ifdef WIN32
	//ActivateConsole();
#endif
	Application application;	

	application.enterMainLoop();
}

