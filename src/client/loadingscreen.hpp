#ifndef LOADINGSCREEN_HPP
#define LOADINGSCREEN_HPP

class Window;

class LoadingScreen
{
	public:
		void setTotalLoadCount(int totalLoads);		
		void progress();		
		
		LoadingScreen(Window& window);
		
	private:
		Window& window;
	
		void draw();
		
		void drawFrame();
		void drawBar();
		
		int totalLoads;		
		int loads;
};

#endif
