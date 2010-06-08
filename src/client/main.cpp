#include "graphics.hpp"
#include "inifile.hpp"
#include "font.hpp"
#include "events.hpp"
#include "sdl.hpp"
#include "container.hpp"
#include "connection.hpp"
#include "ui.hpp"

#include "shared/string.hpp"

#include "container.hpp"

#include "mainmenu.hpp"
#include "settingsmenu.hpp"
#include "connectmenu.hpp"
#include "localgamemenu.hpp"
#include "newlocalgamemenu.hpp"

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

const std::string VIDEO_CONFIG="cfg/video.cfg";

int main(int argc,char** argv)
{
#ifdef WIN32
	ActivateConsole();
#endif

	//init graphics
	IniFile videosettings(VIDEO_CONFIG);

	int width,height,fullscreen,vsync,filter;

	if(!videosettings.getValue(width,"width") || !videosettings.getValue(height,"height"))
	{
		width=640;
		height=480;
	}

	if(!videosettings.getValue(fullscreen,"fullscreen"))
		fullscreen=0;
	if(!videosettings.getValue(vsync,"vsync"))
		vsync=1;
	if(!videosettings.getValue(filter,"filter"))
		filter=LINEAR;

	Sdl sdl;
	
	SDL_WM_SetCaption("Kiihdytyspeli 2","Kiihdytyspeli 2");
	SDL_ShowCursor(false);
	
	Events events(sdl);
	Graphics graphics(sdl,events);	
	
	graphics.setVideoMode(width,height,32,fullscreen,vsync,true);
	Texture::setFilterLimit((TextureFilter)filter);

	FontFace fontface(graphics,"data/fonts/freesans.ttf",64);

	Font::setFontType("title",&fontface,TITLE_SIZE.getY(),Color(0,0,0));
	Font::setFontType("Label",&fontface,ITEM_HEIGHT,Color(0,0,0));
	Font::setFontType("Button",&fontface,ITEM_HEIGHT,Color(0,0,0));
	Font::setFontType("Button.active",&fontface,ITEM_HEIGHT,Color(0.95,0.95,0.95));
	Font::setFontType("Select",&fontface,ITEM_HEIGHT,Color(0,0,0));
	Font::setFontType("Select.active",&fontface,ITEM_HEIGHT,Color(0.95,0.95,0.95));
	Font::setFontType("Field",&fontface,ITEM_HEIGHT,Color(0,0,0));
	
	Window rootwindow;
	
	events.setEventListener(&rootwindow);

	MainMenu mainmenu;
	SettingsMenu settingsmenu(graphics);
	ConnectMenu connectmenu;
	LocalGameMenu localgamemenu;
	NewLocalGameMenu newlocalgamemenu;
	
	rootwindow.addWidget("mainmenu",&mainmenu);
	rootwindow.addWidget("settingsmenu",&settingsmenu);
	rootwindow.addWidget("connectmenu",&connectmenu);
	rootwindow.addWidget("localgamemenu",&localgamemenu);
	rootwindow.addWidget("newlocalgamemenu",&newlocalgamemenu);
	
	settingsmenu.setVisible(false);
	connectmenu.setVisible(false);
	localgamemenu.setVisible(false);
	newlocalgamemenu.setVisible(false);

	rootwindow.resize(graphics);

	Connection connection;

	//init sound	
	/*
	Sound music;
	music.load("data/music/kpthem16.wav");
	music.play();		
	*/
	//mainloop

	int frames=0;
	int time=SDL_GetTicks();
	float fps=0;
	
	float fpsupdate=1000.0;
	
	while(1)
	{
		try
		{
			events.processEvents(graphics);
		}
		catch(ExitException)
		{
			break;			
		}
		
		connection.processMessages();			
			
		graphics.enterGuiMode();
		
		rootwindow.draw(graphics);

		Color(1,1,1).apply();
		fontface.draw(convertToWideString((int)fps),Vector2D(0.75,0.001),0.05);
		
		int x,y;
		
		SDL_GetMouseState(&x,&y);
		
		Vector2D cursorpos=Vector2D(x,y)/graphics.getDisplaySize();
		
		
		glBindTexture(GL_TEXTURE_2D,0);
		
		glBegin(GL_TRIANGLES);
		glVertex2f(cursorpos.getX(),cursorpos.getY());
		glVertex2f(cursorpos.getX()+0.01,cursorpos.getY());
		glVertex2f(cursorpos.getX(),cursorpos.getY()+0.01*graphics.getAspectRatio());
		glEnd();
		graphics.exitGuiMode();
						
		SDL_GL_SwapBuffers();
		
		frames++;
		
		if(SDL_GetTicks()-fpsupdate>=time)
		{
			fps=static_cast<float>(frames)/(static_cast<float>(SDL_GetTicks()-time)/1000.0);
			time=SDL_GetTicks();
			frames=0;
		}
	}
	
	//save settings
	Vector2D displaysize=graphics.getDisplaySize();
	fullscreen=graphics.isFullScreen();
	vsync=graphics.isVsynced();
	filter=Texture::getFilterLimit();		
	
	videosettings.setValue("fullscreen",fullscreen);
	videosettings.setValue("vsync",vsync);
	videosettings.setValue("width",displaysize.getX());
	videosettings.setValue("height",displaysize.getY());
	videosettings.setValue("filter",filter);
	
	videosettings.save(VIDEO_CONFIG);
}

