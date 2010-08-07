#include "application.hpp"
#include "shared/outputredirector.hpp"
#include "shared/crashcatcher.hpp"
#include "shared/crashmessage.hpp"

int main(int argc,char** argv)
{
	CrashMessage crash_message;	
	CrashCatcher crash_catcher(crash_message);
    
	OutputRedirector redirect("client.log");

	Application application;
	application.enterMainLoop();
}

