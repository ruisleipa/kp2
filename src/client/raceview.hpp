#ifndef CLIENT_RACEVIEW_HPP
#define CLIENT_RACEVIEW_HPP

#include "gui/menu.hpp"
#include "gui/widgetloader.hpp"

#include "graphics/texture.hpp"

#include "sounds/sound.hpp"

#include "connection.hpp"

class RaceView : public Menu
{
	public:
		void handleEvent(Event* event);
		
		RaceView(Connection& connection, Container& parent);

	private:
		void sendControlState();
		void drawHandler(DrawEvent* event);
		void quit();
	
		Connection& connection;
		Container& parent;
		
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
				Sound tireSound;
				
				float position;
				float speed;
				float boost;
				float rpm;
				
				class SkidMark
				{
					public:
						float begin;
						float end;
				};
				
				std::list<SkidMark> leftSkid;
				std::list<SkidMark> rightSkid;
				
				float leftSlipRatio;
				float rightSlipRatio;
		};
		
		std::map<int, Vehicle> vehicles;
};

#endif
