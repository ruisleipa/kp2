#include <tr1/memory>

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
#include "errordialog.hpp"

#include "raceview.hpp"

#include "simulationstartevent.hpp"
#include "installerrorevent.hpp"
#include "vehicleerrorevent.hpp"
#include "connectionlostevent.hpp"

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
			if(dynamic_cast<SimulationStartEvent*>(event))
			{
				if(raceView)
				{
					connection.addEventListener(raceView.get());
					menus.removeWidget(*raceView.get());
				}
				
				raceView.reset(new RaceView(connection));
				
				menus.addWidget("raceview", *raceView.get());
				
				menus.showOnlyWidget("raceview");
				
				connection.addEventListener(raceView.get());
			}
		}
		
		RaceStartListener(MenuContainer& menus, Connection& connection):
			menus(menus),
			connection(connection)
		{
		
		}
	
	private:
		MenuContainer& menus;
		Connection& connection;
		
		std::tr1::shared_ptr<RaceView> raceView;
		
};

class ErrorListener: public EventListener
{
	public:
		void handleEvent(Event* event)
		{
			if(dynamic_cast<InstallErrorEvent*>(event))
			{
				InstallErrorEvent* installError = dynamic_cast<InstallErrorEvent*>(event);
				
				dialog.showMessage("Osa autoon mene ei!", installErrors[installError->error]);
			}
			else if(dynamic_cast<VehicleErrorEvent*>(event))
			{
				VehicleErrorEvent* vehicleError = dynamic_cast<VehicleErrorEvent*>(event);
				
				dialog.showMessage("Auto ei toimi!", vehicleErrors[vehicleError->error]);
			}
			else if(dynamic_cast<ConnectionLostEvent*>(event))
			{
				menus.showOnlyWidget("mainmenu");
				dialog.showMessage("", "Yhteys palvelimeen katkesi.");
			}
		}
		
		ErrorListener(ErrorDialog& dialog, MenuContainer& menus):
			dialog(dialog),
			menus(menus)
		{
			installErrors["CYLINDERCOUNT_DOES_NOT_MATCH"] = "Nokka-akseli ei sovi yhteen sylinterikannen kanssa.";
			installErrors["CAMSHAFT_POSITION_DOES_NOT_MATCH"] = "Nokka-akseli ei sovi yhteen sylinterikannen kanssa.";
			installErrors["NO_CYLINDERHEAD_FOR_CAMSHAFT"] = "Asenna ensin sylinterikansi.";
			installErrors["NO_ROOM_FOR_EXTRA_CAMSHAFT"] = "Nokka-akseleita ei voi asentaa enempää.";
			
			installErrors["CYLINDERHEAD_CYLINDERCOUNT_DOES_NOT_MATCH"] = "Sylinterikansi ei sovi yhteen moottorin kanssa.";
			installErrors["CYLINDERHEAD_CAMSHAFTPOSITION_DOES_NOT_MATCH"] = "Sylinterikansi ei sovi yhteen moottorin kanssa.";
			installErrors["CYLINDERHEAD_CYLINDERALIGNMENT_DOES_NOT_MATCH"] = "Sylinterikansi ei sovi yhteen moottorin kanssa.";
			installErrors["NO_ENGINE_FOR_CYLINDERHEAD"] = "Asenna ensin moottori.";
			installErrors["NO_ROOM_FOR_EXTRA_CYLINDERHEAD"] = "Sylinterikansia ei voi asentaa enempää.";
			
			installErrors["ENGINE_TOO_LARGE_FOR_CHASSIS"] = "Moottori on liian iso koriin.";
			installErrors["NO_ROOM_FOR_EXTRA_ENGINE"] = "Moottoreita ei voi asentaa enempää.";
			
			installErrors["EXHAUSTMANIFOLD_CYLINDERCOUNT_DOES_NOT_MATCH"] = "Pakosarja ei sovi yhteen sylinterikannen kanssa.";
			installErrors["EXHAUSTMANIFOLD_CYLINDERALIGNMENT_DOES_NOT_MATCH"] = "Pakosarja ei sovi yhteen sylinterikannen kanssa.";
			installErrors["NO_ROOM_FOR_EXTRA_EXHAUSTMANIFOLD"] = "Pakosarjoja ei voi asentaa enempää.";
			
			installErrors["INTAKEMANIFOLD_CYLINDERCOUNT_DOES_NOT_MATCH"] = "Imusarja ei sovi yhteen sylinterikannen kanssa.";
			installErrors["INTAKEMANIFOLD_CYLINDERALIGNMENT_DOES_NOT_MATCH"] = "Imusarja ei sovi yhteen sylinterikannen kanssa.";
			installErrors["NO_ROOM_FOR_EXTRA_INTAKEMANIFOLD"] = "Imusarjoja ei voi asentaa enempää.";
			
			vehicleErrors["ENGINE_MISSING"] = "Asenna moottori.";
			vehicleErrors["INTAKEMANIFOLD_MISSING"] = "Asenna imusarja.";
			vehicleErrors["EXHAUSTMANIFOLD_MISSING"] = "Asenna pakosarja.";
			vehicleErrors["TRANSMISSION_MISSING"] = "Asenna vaihteisto.";
			vehicleErrors["TIRE_MISSING"] = "Asenna vaihteisto.";
		}
	
	private:
		ErrorDialog& dialog;
		MenuContainer& menus;
		
		std::map<std::string, std::string> installErrors;
		std::map<std::string, std::string> vehicleErrors;
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
	
	ErrorDialog errorDialog;
	
	ErrorListener errorListener(errorDialog, menuContainer);
	connection.addEventListener(&errorListener);
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
	menuContainer.addWidget("errordialog",errorDialog);
	menuContainer.showOnlyWidget("mainmenu");
	
	RaceStartListener raceStartListener(menuContainer, connection);
	connection.addEventListener(&raceStartListener);
	
	RootContainer rootContainer(window,events);	
	rootContainer.addWidget(menuContainer, "0px", "0px", "100%", "100%");
	
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
	
	return 0;
}

