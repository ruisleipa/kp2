#include "raceview.hpp"

#include "gauge.hpp"
#include "simulationstartevent.hpp"
#include "simulationvehicledataevent.hpp"
#include "simulationvehiclestateevent.hpp"
#include "simulationvehicleresultevent.hpp"
#include "protocol/controlstate.hpp"
#include "gui/label.hpp"
#include "gui/button.hpp"

void RaceView::handleEvent(Event* event)
{
	gearUp = false;
	gearDown = false;

	if(dynamic_cast<KeyDownEvent*>(event))
	{
		KeyDownEvent* keyDown = dynamic_cast<KeyDownEvent*>(event);
		
		if(keyDown->getKey() == SDLK_UP)
			throttle = 1.0;
		if(keyDown->getKey() == SDLK_s)
			ignition = true;
		if(keyDown->getKey() == SDLK_a)
			gearUp = true;
		if(keyDown->getKey() == SDLK_z)
			gearDown = true;
		if(keyDown->getKey() == SDLK_SPACE)
			clutch = 0.0;
			
		sendControlState();
	}
	
	if(dynamic_cast<KeyUpEvent*>(event))
	{
		KeyUpEvent* keyUp = dynamic_cast<KeyUpEvent*>(event);
		
		if(keyUp->getKey() == SDLK_UP)
			throttle = 0.0;
		if(keyUp->getKey() == SDLK_s)
			ignition = false;
		if(keyUp->getKey() == SDLK_SPACE)
			clutch = 1.0;
		
		sendControlState();
	}
	
	if(dynamic_cast<SimulationVehicleDataEvent*>(event))
	{
		SimulationVehicleDataEvent* dataEvent = dynamic_cast<SimulationVehicleDataEvent*>(event);
		
		Vehicle vehicle;
		
		vehicle.texture = Texture("gamedata/vehicleimages/" + dataEvent->data.imageName);
		vehicle.width = dataEvent->data.width;
		
		
		vehicles[dataEvent->data.id] = vehicle;
		
		vehicles[dataEvent->data.id].tireSound.load("data/sounds/simulation/burnout.wav");
		vehicles[dataEvent->data.id].tireSound.setLooping(true);
	}
	
	if(dynamic_cast<SimulationVehicleStateEvent*>(event))
	{
		SimulationVehicleStateEvent* stateEvent = dynamic_cast<SimulationVehicleStateEvent*>(event);
		
		Vehicle& vehicle = vehicles[stateEvent->state.id];
		
		vehicle.position = stateEvent->state.position;
		vehicle.speed = stateEvent->state.speed;
		vehicle.rpm = stateEvent->state.engineSpeedInRpm;
		vehicle.boost = stateEvent->state.boostPressure;
		
		if(vehicle.leftSlipRatio < 0.05 && stateEvent->state.leftTireSlipRatio > 0.05)
		{
			Vehicle::SkidMark skid;
			skid.begin = vehicle.position;
			skid.end = vehicle.position;
			
			vehicle.leftSkid.push_back(skid);
		}
		
		if(vehicle.leftSlipRatio > 0.05)
			vehicle.leftSkid.back().end = vehicle.position;
			
		if(vehicle.rightSlipRatio < 0.05 && stateEvent->state.rightTireSlipRatio > 0.05)
		{
			Vehicle::SkidMark skid;
			skid.begin = vehicle.position;
			skid.end = vehicle.position;
			
			vehicle.rightSkid.push_back(skid);
		}
		
		if(vehicle.rightSlipRatio > 0.05)
			vehicle.rightSkid.back().end = vehicle.position;
		
		vehicle.leftSlipRatio = stateEvent->state.leftTireSlipRatio;
		vehicle.rightSlipRatio = stateEvent->state.rightTireSlipRatio;
		
		std::cout << vehicle.leftSlipRatio << " " << vehicle.rightSlipRatio << std::endl;
		
		if(vehicle.leftSlipRatio > 0.05 || vehicle.rightSlipRatio > 0.05)
		{
			if(!vehicle.tireSound.isPlaying())
				vehicle.tireSound.play();
		}
		else
		{
			vehicle.tireSound.stop();
		}
		
		
	}
	
	if(dynamic_cast<SimulationVehicleResultEvent*>(event))
	{
		SimulationVehicleResultEvent* resultEvent = dynamic_cast<SimulationVehicleResultEvent*>(event);
		
		std::stringstream ss;
		
		ss << "Reaktioaika: " << resultEvent->result.reactionTime << "\n";
		ss << "Matka-aika: " << resultEvent->result.elapsedTime << "\n";
		ss << "Kokonaisaika: " << resultEvent->result.totalTime << "\n";
		ss << "Huippunopeus: " << resultEvent->result.topSpeed * 3.6 << " km/h\n";
		
		getChildByName<Label>("resultsLabel").setText(ss.str());
		getChildByName("results").setVisible(true);
	}
	
	if(dynamic_cast<DrawEvent*>(event))
		drawHandler(dynamic_cast<DrawEvent*>(event));
	
	Menu::handleEvent(event);
}

RaceView::RaceView(Connection& connection, Container& parent):
	connection(connection),
	parent(parent),
	ignition(false),
	gearUp(false),
	gearDown(false),
	throttle(0),
	brake(0),
	clutch(1),
	position(0),
	loader("data/ui/raceview.ui"),
	trackStart("data/track/start.png"),
	track("data/track/track.png"),
	tree("data/track/tree.png")
{
	addWidget(loader.getRootWidget(), "0px", "0px", "100%", "100%");
	
	getChildByName<Button>("quitButton").setClickHandler(std::tr1::bind(&RaceView::quit, this));
}

void RaceView::sendControlState()
{
	Protocol::ControlState state;
	
	state.ignition = ignition;
	state.throttle = throttle;
	state.clutch = clutch;
	state.brake = 0;
	state.gearUp = gearUp;
	state.gearDown = gearDown;
	
	connection.sendControlState(state);
}

void RaceView::quit()
{
	connection.quitSimulation();
	
	parent.showOnlyWidget("careermenu");
}

void RaceView::drawHandler(DrawEvent* event)
{
	dynamic_cast<Gauge&>(getChildByName("rpmGauge")).setValue(vehicles[0].rpm);
	dynamic_cast<Gauge&>(getChildByName("boostGauge")).setValue(vehicles[0].boost);
	dynamic_cast<Gauge&>(getChildByName("speedGauge")).setValue(vehicles[0].speed);

	float viewWidthInMeters = 25.0;
	float viewHeightInMeters = viewWidthInMeters / event->getAreaSize().getX() * event->getAreaSize().getY();
	
	float startingLine = 0.0;
	
	const float QUARTER_MILE = 402.336;
	float finishLine = QUARTER_MILE;
	
	float trackWidth = 6.0;
	
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	gluOrtho2D(-viewWidthInMeters / 2.0, viewWidthInMeters / 2.0, viewHeightInMeters, 0);
	glMatrixMode(GL_MODELVIEW);
	
	glPushMatrix();
	glClearColor(0, 0.5, 0, 0);
	glClear(GL_COLOR_BUFFER_BIT);
	
	Texture().bind();
	
	float positionValue = vehicles[0].position;
	
	glTranslatef(0, -(std::min(positionValue, finishLine) - viewHeightInMeters / 2.0), 0);
	
	Color(1, 1, 1, 1).apply();
	
	Vector2D position(-trackWidth / 2.0, -10);
	
	Vector2D trackSize(trackWidth, trackWidth / track.getSize().getX() * track.getSize().getY());
	
	for(int i = 0; i < QUARTER_MILE / trackSize.getY() + 10; ++i)
	{
		track.draw(position, trackSize);
		position += Vector2D(0, trackSize.getY());
	}
	
	Texture().bind();
	
	glLineWidth(4.0);
	glBegin(GL_LINES);
		glVertex2f(-trackWidth / 2.0, startingLine);
		glVertex2f(trackWidth / 2.0, startingLine);
	glEnd();
	
	glBegin(GL_LINES);
		glVertex2f(-trackWidth / 2.0, finishLine);
		glVertex2f(trackWidth / 2.0, finishLine);
	glEnd();
	
	int vehicleIndex = 0;
	
	for(std::map<int, Vehicle>::iterator i = vehicles.begin(); i != vehicles.end(); ++i)
	{
		Vehicle& vehicle = i->second;
		
		Texture& texture = vehicle.texture;
		
		float vehicleLength = vehicle.width / texture.getSize().getX() * texture.getSize().getY();
		
		float vehicleX;
		
		if(vehicleIndex == 0)
			vehicleX = (trackWidth / 4.0);
		else
			vehicleX = -(trackWidth / 4.0);
		
		Color(0, 0, 0, 1).apply();
		
		float leftTirePosition = vehicleX + (vehicle.width / 2.0) - (vehicle.width / 10.0);
		
		for(std::list<Vehicle::SkidMark>::iterator j = vehicle.leftSkid.begin(); j != vehicle.leftSkid.end(); ++j)
		{
			glBegin(GL_LINES);
			
			glVertex2f(leftTirePosition, j->begin);
			glVertex2f(leftTirePosition, j->end);
			
			glEnd();
		}
		
		float rightTirePosition = vehicleX - (vehicle.width / 2.0) + (vehicle.width / 10.0);
		
		for(std::list<Vehicle::SkidMark>::iterator j = vehicle.rightSkid.begin(); j != vehicle.rightSkid.end(); ++j)
		{
			glBegin(GL_LINES);
			
			glVertex2f(rightTirePosition, j->begin);
			glVertex2f(rightTirePosition, j->end);
			
			glEnd();
		}
		
		Color(1, 1, 1, 1).apply();
		
		texture.draw(Vector2D(vehicleX - (vehicle.width / 2.0), vehicle.position - vehicleLength), Vector2D(vehicle.width, vehicleLength));
		
		vehicleIndex++;
	}
	
	glPopMatrix();
	
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
}
