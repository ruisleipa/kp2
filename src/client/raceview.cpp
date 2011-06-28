#include "raceview.hpp"

#include "gauge.hpp"
#include "simulationstartevent.hpp"
#include "simulationvehicledataevent.hpp"
#include "simulationvehiclestateevent.hpp"
#include "simulationvehicleresultevent.hpp"
#include "protocol/controlstate.hpp"
#include "gui/label.hpp"

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
	}
	
	if(dynamic_cast<SimulationVehicleStateEvent*>(event))
	{
		SimulationVehicleStateEvent* stateEvent = dynamic_cast<SimulationVehicleStateEvent*>(event);
		
		Vehicle& vehicle = vehicles[stateEvent->state.id];
		
		vehicle.position = stateEvent->state.position;
		vehicle.speed = stateEvent->state.speed;
		vehicle.rpm = stateEvent->state.engineSpeedInRpm;
		vehicle.boost = stateEvent->state.boostPressure;
	}
	
	if(dynamic_cast<SimulationVehicleResultEvent*>(event))
	{
		SimulationVehicleResultEvent* resultEvent = dynamic_cast<SimulationVehicleResultEvent*>(event);
		
		std::stringstream ss;
		
		ss << "Reaktioaika: " << resultEvent->result.reactionTime << "\n";
		ss << "Matka-aika: " << resultEvent->result.elapsedTime << "\n";
		ss << "Kokonaisaika: " << resultEvent->result.totalTime << "\n";
		ss << "Huippunopeus: " << resultEvent->result.topSpeed * 3.6 << " km/h\n";
		
		dynamic_cast<Label&>(getChildByName("debugLabel")).setText(ss.str());
	}
	
	if(dynamic_cast<DrawEvent*>(event))
		drawHandler(dynamic_cast<DrawEvent*>(event));
	
	Menu::handleEvent(event);
}

RaceView::RaceView(Connection& connection):
	connection(connection),
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
	connection.addEventHandler(std::tr1::bind(&RaceView::onConnectionEvent,this,std::tr1::placeholders::_1));

	addWidget(loader.getRootWidget(), "0px", "0px", "100%", "100%");
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

void RaceView::onConnectionEvent(Connection& connection)
{

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
	
	glTranslatef(0, -(std::min(positionValue, finishLine) - 4), 0);
	
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
		
		float vehiceLength = vehicle.width / texture.getSize().getX() * texture.getSize().getY();
		
		if(vehicleIndex == 0)
			texture.draw(Vector2D((trackWidth / 4.0) - (vehicle.width / 2.0), vehicle.position - vehiceLength), Vector2D(vehicle.width, vehiceLength));
		else
			texture.draw(Vector2D((vehicle.width / 2.0) - (trackWidth / 4.0), vehicle.position - vehiceLength), Vector2D(vehicle.width, vehiceLength));
			
		vehicleIndex++;
	}
	
	glPopMatrix();
	
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
}
