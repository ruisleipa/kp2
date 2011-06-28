#ifndef CLIENT_RACEVIEW_HPP
#define CLIENT_RACEVIEW_HPP

#include "gui/menu.hpp"
#include "gui/widgetloader.hpp"
#include "graphics/texture.hpp"

#include "connection.hpp"

class RaceView : public Menu
{
	public:
		void handleEvent(Event* event);
		
		RaceView(Connection& connection);

	private:
		void sendControlState();
		void drawHandler(DrawEvent* event);
		void onConnectionEvent(Connection& connection);
	
		Connection& connection;
		
		bool ignition;
		bool gearUp;
		bool gearDown;
		float throttle;
		float brake;
		float clutch;
		
		float position;
		
		WidgetLoader loader;
		
		Texture trackStart;
		Texture track;
		Texture tree;
		
		class Vehicle
		{
			public:
				Texture texture;
				float width;
				
				float position;
				float speed;
				float boost;
				float rpm;
		};
		
		std::map<int, Vehicle> vehicles;
};

#endif
