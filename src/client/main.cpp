#include "graphics.hpp"
#include "inifile.hpp"
#include "font.hpp"
#include "events.hpp"
#include "ui.hpp"
#include "sdl.hpp"
#include "shared/string.hpp"

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

	int width,height,fullscreen,vsync;

	if(!videosettings.getValue(width,"width") || !videosettings.getValue(height,"height"))
	{
		width=640;
		height=480;
	}

	if(!videosettings.getValue(fullscreen,"fullscreen"))
		fullscreen=0;
	if(!videosettings.getValue(vsync,"vsync"))
		vsync=1;

	Sdl::getInstance();
	
	SDL_WM_SetCaption("Kiihdytyspeli 2","Kiihdytyspeli 2");
	SDL_ShowCursor(false);
	
	Graphics::getInstance().setVideoMode(width,height,32,fullscreen,vsync,true);

	//init ui
	
	FontFace fontface("data/fonts/freesans.ttf",64);
	Font font(&fontface,ITEM_HEIGHT,Color(0,0,0));
	Font passivefont(&fontface,ITEM_HEIGHT,Color(0,0,0));	
	Font activefont(&fontface,ITEM_HEIGHT,Color(0.95,0.95,0.95));
	Font titlefont(&fontface,TITLE_SIZE.getY(),Color(0,0,0));
	
	Ui::getInstance().setFont("title",&titlefont);
	Ui::getInstance().setFont("Label",&passivefont);
	Ui::getInstance().setFont("Button",&font);
	Ui::getInstance().setFont("Button.active",&activefont);
	Ui::getInstance().setFont("Select",&font);
	Ui::getInstance().setFont("Select.active",&activefont);
	Ui::getInstance().setFont("Field",&passivefont);
	
	Events::getInstance().setEventListener(&Ui::getInstance());
	
	MainMenu mainmenu;
	SettingsMenu settingsmenu;
	ConnectMenu connectmenu;
	LocalGameMenu localgamemenu;
	NewLocalGameMenu newlocalgamemenu;
	
	Ui::getInstance().addView("mainmenu",&mainmenu);
	Ui::getInstance().addView("settingsmenu",&settingsmenu);
	Ui::getInstance().addView("connectmenu",&connectmenu);
	Ui::getInstance().addView("localgamemenu",&localgamemenu);
	Ui::getInstance().addView("newlocalgamemenu",&newlocalgamemenu);
	
	Ui::getInstance().goToView("mainmenu");	
	
	Ui::getInstance().calculateLayouts();

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
			Events::getInstance().processEvents();
		}
		catch(ExitException)
		{
			break;			
		}			
			
		Graphics::getInstance().enterGuiMode();
		
		Ui::getInstance().draw();
		
		Color(1,1,1).apply();
		fontface.draw(convertToWideString((int)fps),Vector2D(0.75,0.001),0.05);
		
		int x,y;
		
		SDL_GetMouseState(&x,&y);
		
		Vector2D cursorpos=Vector2D(x,y)/Graphics::getInstance().getDisplaySize();
		
		glBindTexture(GL_TEXTURE_2D,0);
		
		glBegin(GL_TRIANGLES);
		glVertex2f(cursorpos.getX(),cursorpos.getY());
		glVertex2f(cursorpos.getX()+0.01,cursorpos.getY());
		glVertex2f(cursorpos.getX(),cursorpos.getY()+0.01*Graphics::getInstance().getAspectRatio());
		glEnd();
		
		Graphics::getInstance().exitGuiMode();
						
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
	Vector2D displaysize=Graphics::getInstance().getDisplaySize();
	fullscreen=Graphics::getInstance().isFullscreen();
	vsync=Graphics::getInstance().isVsynced();	
	
	videosettings.setValue("fullscreen",fullscreen);
	videosettings.setValue("vsync",vsync);
	videosettings.setValue("width",displaysize.getX());
	videosettings.setValue("height",displaysize.getY());
	
	videosettings.save(VIDEO_CONFIG);
}

