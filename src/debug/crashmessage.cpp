#include "crashmessage.hpp"

#ifdef WIN32
#include <windows.h>
#else
#include <iostream>
#endif

void CrashMessage::showMessage()
{
#ifdef WIN32
	const WCHAR* errorMessage=L"Kiihdytyspeli 2 lakkasi toimimasta.\n\n"
	L"Pelin hakemistossa olevista log-päätteisistä tiedostoista löytyy "
	L"kehittäjille tarkoitettua lisätietoa virheestä. Liitä ne osaksi "
	L"vikaraporttia.";

	const WCHAR* errorCaption=L"Kiihdytyspeli 2";
	
	MessageBoxW(NULL, errorMessage, errorCaption, MB_OK | MB_ICONERROR);
#else
	std::cerr << "Kiihdytyspeli 2 kaatui. Lähetä pelin "
	"hakemistossa olevat server.log ja client.log -nimiset tiedostot "
	"Siilisoftwaren foorumille. Lähetä myös kuvaus siitä mitä olit "
	"tekemässä kun peli kaatui." << std::endl;
#endif
}
