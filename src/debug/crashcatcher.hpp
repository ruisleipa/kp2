#ifndef CRASHCATCHER_HPP
#define CRASHCATCHER_HPP

#ifdef WIN32
#include <excpt.h>
#endif

class CrashMessage;
class CrashCatcher;

#ifdef WIN32
struct ExceptionRegistration
{
	ExceptionRegistration* prev;
	PEXCEPTION_HANDLER handler;
	CrashCatcher* object;
};
#endif

class CrashCatcher
{
	public:
		CrashCatcher(CrashMessage& crash_message);
		~CrashCatcher();

	private:
		void installCatcher();	
		void uninstallCatcher();	
		
#ifdef WIN32
		static LONG catchCrash(PEXCEPTION_RECORD, EXCEPTION_REGISTRATION*, PCONTEXT, PEXCEPTION_RECORD);
#else
		static void catchCrash(int signal_number);
#endif
		void handleCrash();
				
		void printStackTrace();		
		void printStackTraceHeader();
		void iterateStack();
		void showMessage();
		
		CrashMessage& crashMessage;
#ifdef WIN32
		ExceptionRegistration exceptionRegistration;
#else
		static CrashCatcher* catcher;
#endif
};

#endif // CRASHCATCHER_HPP
