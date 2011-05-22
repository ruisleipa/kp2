#include "utils/outputredirector.hpp"
#include "debug/crashcatcher.hpp"
#include "debug/crashmessage.hpp"
#include "debug/stacktrace.hpp"

#include "utils/sdl.hpp"
#include "graphics/window.hpp"
#include "graphics/color.hpp"
#include "graphics/fontface.hpp"
#include "graphics/texture.hpp"
#include "graphics/texturecollection.hpp"
#include "utils/timer.hpp"
#include "events/events.hpp"

#include "gui/rootcontainer.hpp"
#include "gui/menucontainer.hpp"
#include "gui/tabbedmenu.hpp"

#include "newlocalgamemenu.hpp"
#include "localgamemenu.hpp"
#include "mainmenu.hpp"
#include "settingsmenu.hpp"
#include "careermenu.hpp"

#include "carshopmenu.hpp"
#include "carlistmenu.hpp"

#include "partshopmenu.hpp"
#include "installpartsmenu.hpp"

#include "loadingscreen.hpp"
#include "fontloader.hpp"

#include "connection.hpp"
#include "net/socket.hpp"

#include "sounds/musicplayer.hpp"

void startGame()
{
	Sdl sdl;
	Window window(sdl);
	Events events(window);
	
	MusicPlayer musicPlayer;
	
	LoadingScreen loadingScreen(window);
	loadingScreen.setTotalLoadCount(13);

	FontLoader fontLoader(window);	
	
	TextureCollection backgroundTextures;
	
	backgroundTextures.addTexture("image00",Texture("data/images/backgrounds/block.png"));
	loadingScreen.progress();
	backgroundTextures.addTexture("image01",Texture("data/images/backgrounds/brakedisk.png"));
	loadingScreen.progress();
	backgroundTextures.addTexture("image02",Texture("data/images/backgrounds/charger.png"));
	loadingScreen.progress();
	backgroundTextures.addTexture("image03",Texture("data/images/backgrounds/cooler.png"));
	loadingScreen.progress();
	backgroundTextures.addTexture("image04",Texture("data/images/backgrounds/cylinderhead.png"));
	loadingScreen.progress();
	backgroundTextures.addTexture("image05",Texture("data/images/backgrounds/diff.png"));
	loadingScreen.progress();
	backgroundTextures.addTexture("image06",Texture("data/images/backgrounds/engine.png"));
	loadingScreen.progress();
	backgroundTextures.addTexture("image07",Texture("data/images/backgrounds/engine1.png"));
	loadingScreen.progress();
	backgroundTextures.addTexture("image08",Texture("data/images/backgrounds/engine2.png"));
	loadingScreen.progress();
	backgroundTextures.addTexture("image09",Texture("data/images/backgrounds/exhaust.png"));
	loadingScreen.progress();
	backgroundTextures.addTexture("image10",Texture("data/images/backgrounds/intake.png"));
	loadingScreen.progress();
	backgroundTextures.addTexture("image11",Texture("data/images/backgrounds/tire.png"));
	loadingScreen.progress();
	backgroundTextures.addTexture("image12",Texture("data/images/backgrounds/tools.png"));
	loadingScreen.progress();
	
	TextureCollection mainmenuTextures;
	mainmenuTextures.addTexture("title",Texture("data/images/kp2_txt.png"));

	TextureCollection careerTextures;
	careerTextures.addTexture("background",Texture("data/images/careermenu.png"));	
	
	Connection connection;
	
	MenuContainer topLevelGameMenus(backgroundTextures);
	
	MainMenu mainMenu(topLevelGameMenus, mainmenuTextures);
	
	SettingsMenu settingsMenu(topLevelGameMenus, window, musicPlayer);
	LocalGameMenu localGameMenu(topLevelGameMenus);
	NewLocalGameMenu newLocalGameMenu(topLevelGameMenus, connection);	
	
	TabbedMenu garageMenu;	
	
	CarShopMenu carShopMenu(connection);
	CarListMenu carListMenu(connection);
	
	garageMenu.addTab("Autokauppa",carShopMenu);
	garageMenu.addTab("Autotalli",carListMenu);	
	
	topLevelGameMenus.addWidget("garage",garageMenu);
	
	TabbedMenu tuningMenu;	
	PartShopMenu partShopMenu(connection);
	InstallPartsMenu installPartsMenu(connection);	
	tuningMenu.addTab("Osakauppa",partShopMenu);
	tuningMenu.addTab("Asenna osia",installPartsMenu);
	
	topLevelGameMenus.addWidget("tuning",tuningMenu);
	
	topLevelGameMenus.showOnlyWidget("");
	
	CareerMenu careerMenu(careerTextures,topLevelGameMenus,connection);
		
	MenuContainer menuContainer(backgroundTextures);	
	menuContainer.addWidget("mainmenu",mainMenu);
	menuContainer.addWidget("settingsmenu",settingsMenu);
	menuContainer.addWidget("localgamemenu",localGameMenu);	
	menuContainer.addWidget("newlocalgamemenu",newLocalGameMenu);	
	menuContainer.addWidget("careermenu",careerMenu);	
	menuContainer.showOnlyWidget("mainmenu");
	menuContainer.setSize(Vector2D(1,1));
	
	RootContainer rootContainer(window,events);	
	rootContainer.addWidget(menuContainer);
	
	rootContainer.resize(window);
	
	bool running = true;
	
	while(running)
	{
	
		glClear(GL_COLOR_BUFFER_BIT);
		
		EventArea eventArea(window, Vector2D(0,0), window.getSize());
		DrawEvent drawEvent(eventArea);
		
		rootContainer.handleEvent(&drawEvent);
		
		Color(1,1,1).apply();
		SDL_GL_SwapBuffers();		
		
		try
		{
			connection.processMessages();		
		}
		catch(ConnectionClosedException)
		{
			menuContainer.showOnlyWidget("mainmenu");
		}
		
		try
		{
			events.processEvents();
		}
		catch(ExitException)
		{
			running = false;
		}
		
		musicPlayer.update();

		if(window.hasModeChanged())
		{
#ifdef WIN32
			fontLoader.freeTextures();			
			backgroundTextures.freeTextures();
			mainmenuTextures.freeTextures();
			careerTextures.freeTextures();
			
			fontLoader.reload();
#endif		
			rootContainer.resize(window);
			
			window.clearModeChangeFlag();
		}
	}
}

int main(int argc,char** argv)
{
	CrashMessage crashMessage;	
	CrashCatcher crashCatcher(crashMessage);    
	OutputRedirector outputRedirector("client.log");

	try
	{
		startGame();
	}
	catch(std::runtime_error error)
	{
		std::cerr << "Runtime error: " << error.what() << std::endl;
		
		crashMessage.showMessage();
	}
	catch(std::exception error)
	{
		std::cerr << "Error: " << error.what() << std::endl;
		
		crashMessage.showMessage();
	}
	catch(...)
	{
		std::cerr << "Unknown error" << std::endl;
		
		crashMessage.showMessage();
	}
}

