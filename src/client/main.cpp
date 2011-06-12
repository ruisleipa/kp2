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
#include "utils/directory.hpp"
#include "events/events.hpp"

#include "gui/rootcontainer.hpp"
#include "gui/menucontainer.hpp"
#include "gui/tabbedmenu.hpp"

#include "remotegamemenu.hpp"
#include "newlocalgamemenu.hpp"
#include "localgamemenu.hpp"
#include "mainmenu.hpp"
#include "settingsmenu.hpp"
#include "careermenu.hpp"

#include "carshopmenu.hpp"
#include "carlistmenu.hpp"

#include "partshopmenu.hpp"
#include "installpartsmenu.hpp"
#include "performancemenu.hpp"

#include "raceview.hpp"

#include "racestartevent.hpp"

#include "loadingscreen.hpp"
#include "fontloader.hpp"

#include "connection.hpp"
#include "net/socket.hpp"

#include "sounds/musicplayer.hpp"

class RaceStartListener: public EventListener
{
	public:
		void handleEvent(Event* event)
		{
			if(dynamic_cast<RaceStartEvent*>(event))
				menus.showOnlyWidget("raceview");
		}
		
		RaceStartListener(MenuContainer& menus):
			menus(menus)
		{
		
		}
	
	private:
		MenuContainer& menus;
		
};

void startGame()
{
	Sdl sdl;
	Window window(sdl);
	Events events(window);
	
	MusicPlayer musicPlayer;
	
	LoadingScreen loadingScreen(window);
	
	FontLoader fontLoader(window);	
	
	TextureCollection backgroundTextures;
	
	const std::string BACKGROUND_DIR = "data/images/backgrounds/";
	
	std::vector<std::string> backgroundFiles = readDirectory("data/images/backgrounds/");
	
	loadingScreen.setTotalLoadCount(backgroundFiles.size());
	
	for(std::vector<std::string>::size_type i = 0; i < backgroundFiles.size(); ++i)
	{
		std::stringstream ss;
		
		ss << "image" << i;
	
		backgroundTextures.addTexture(ss.str(), Texture(BACKGROUND_DIR + backgroundFiles[i]));
		loadingScreen.progress();
	}	
	
	TextureCollection mainmenuTextures;
	mainmenuTextures.addTexture("title",Texture("data/images/kp2_txt.png"));

	TextureCollection careerTextures;
	careerTextures.addTexture("background",Texture("data/images/careermenu.png"));	
	
	Connection connection;
	
	MenuContainer topLevelGameMenus(backgroundTextures);
	
	TabbedMenu garageMenu;	
	
	CarShopMenu carShopMenu(connection);
	CarListMenu carListMenu(connection);
	
	garageMenu.addTab("Autokauppa",carShopMenu);
	garageMenu.addTab("Autotalli",carListMenu);	
	
	topLevelGameMenus.addWidget("garage",garageMenu);
	
	TabbedMenu tuningMenu;	
	PartShopMenu partShopMenu(connection);
	InstallPartsMenu installPartsMenu(connection);	
	PerformanceMenu performanceMenu(connection);	
	tuningMenu.addTab("Osakauppa", partShopMenu);
	tuningMenu.addTab("Asenna osia", installPartsMenu);
	tuningMenu.addTab("Säädöt", performanceMenu);
	
	topLevelGameMenus.addWidget("tuning",tuningMenu);
	
	topLevelGameMenus.showOnlyWidget("");
	
	MenuContainer menuContainer(backgroundTextures);	
	
	MenuContainer asd(backgroundTextures);
	
	MainMenu mainMenu(menuContainer, mainmenuTextures);	
	SettingsMenu settingsMenu(menuContainer, window, musicPlayer);
	LocalGameMenu localGameMenu(menuContainer);
	NewLocalGameMenu newLocalGameMenu(menuContainer, connection);	
	RemoteGameMenu remoteGameMenu(menuContainer, connection);	
	CareerMenu careerMenu(careerTextures,topLevelGameMenus,connection);	
	RaceView raceView(connection);
	connection.addEventListener(&raceView);
	
	menuContainer.addWidget("mainmenu",mainMenu);
	menuContainer.addWidget("settingsmenu",settingsMenu);
	menuContainer.addWidget("localgamemenu",localGameMenu);	
	menuContainer.addWidget("newlocalgamemenu",newLocalGameMenu);	
	menuContainer.addWidget("remotegamemenu",remoteGameMenu);	
	menuContainer.addWidget("careermenu",careerMenu);	
	menuContainer.addWidget("raceview",raceView);	
	menuContainer.showOnlyWidget("mainmenu");
	
	RaceStartListener raceStartListener(menuContainer);
	connection.addEventListener(&raceStartListener);
	
	RootContainer rootContainer(window,events);	
	rootContainer.addWidget(menuContainer, "0px", "0px", "100%", "100%");
	
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
	catch(std::exception& error)
	{
		std::cerr << "Error: " << error.what() << std::endl;
		
		std::cerr << typeid(error).name() << std::endl;
		
		crashMessage.showMessage();
	}
	catch(...)
	{
		std::cerr << "Unknown error" << std::endl;
		
		crashMessage.showMessage();
	}
}

