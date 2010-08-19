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

#include "mainmenu.hpp"
#include "settingsmenu.hpp"

#include "loadingscreen.hpp"
#include "fontloader.hpp"

void startGame()
{
	Sdl sdl;
	Window window(sdl);
	Events events(window);
	
	LoadingScreen loadingScreen;
	loadingScreen.setTotalLoadCount(13);

	FontLoader fontLoader;	
	
	//Load textures
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
	mainmenuTextures.addTexture("title",Texture("data/images/kp2"));
	
	//Init ui
	RootContainer rootContainer(window,events);
	
	MainMenu mainMenu(mainmenuTextures);
	SettingsMenu settingsMenu(window,mainmenuTextures);
	
	rootContainer.addChild("mainmenu",mainMenu);
	rootContainer.addChild("settingsmenu",settingsMenu);
	
	rootContainer.doResize(window);
	
	while(1)
	{
		glClear(GL_COLOR_BUFFER_BIT);
		rootContainer.doDraw(window);
		SDL_GL_SwapBuffers();		
		events.processEvents();				
	}
	
	window.saveSettings();
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

