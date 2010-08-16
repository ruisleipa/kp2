#ifndef LOADINGSCREEN_HPP
#define LOADINGSCREEN_HPP

class LoadingScreen
{
	public:
		void setTotalLoadCount(int totalLoads);		
		void progress();		
		
		LoadingScreen();
		
	private:
		void draw();
		
		void drawFrame();
		void drawBar();
		
		int totalLoads;		
		int loads;
};

#endif
