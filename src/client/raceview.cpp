#include "raceview.hpp"

#include "gauge.hpp"
#include "racestateevent.hpp"
#include "protocol/racecontrolstate.hpp"
#include "gui/label.hpp"

void RaceView::handleEvent(Event* event)
{
	bool gearUp = false;
	bool gearDown = false;

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
	}
	
	if(dynamic_cast<RaceStateEvent*>(event))
	{
		RaceStateEvent* stateEvent = dynamic_cast<RaceStateEvent*>(event);
		
		dynamic_cast<Gauge&>(getChildByName("rpmGauge")).setValue(stateEvent->state.engineSpeedInRpm);
		dynamic_cast<Gauge&>(getChildByName("boostGauge")).setValue(stateEvent->state.boostPressure);
		dynamic_cast<Gauge&>(getChildByName("speedGauge")).setValue(stateEvent->state.speed);
		
		std::stringstream ss;
		
		ss << "RPM: " << stateEvent->state.engineSpeedInRpm << "\n";
		ss << "boostPressure: " << stateEvent->state.boostPressure << "\n";
		ss << "time: " << stateEvent->state.time << "\n";
		ss << "position: " << stateEvent->state.position << "\n";
		ss << "speed: " << stateEvent->state.speed << "\n";
		
		dynamic_cast<Label&>(getChildByName("debugLabel")).setText(ss.str());
		
		position = stateEvent->state.position;
	}
	
	if(dynamic_cast<DrawEvent*>(event))
		drawHandler(dynamic_cast<DrawEvent*>(event));
	
	Protocol::RaceControlState state;
	
	state.ignition = ignition;
	state.throttle = throttle;
	state.clutch = clutch;
	state.brake = 0;
	state.gearUp = gearUp;
	state.gearDown = gearDown;
	
	connection.sendRaceControlState(state);
	
	Menu::handleEvent(event);
}

RaceView::RaceView(Connection& connection):
	connection(connection),
	ignition(false),
	throttle(0),
	brake(0),
	clutch(1),
	position(0),
	loader("data/ui/raceview.ui"),
	trackStart("data/track/start.png"),
	track("data/track/track.png"),
	tree("data/track/tree.png"),
	vehicle1("gamedata/vehicleimages/fiat_uno.png")
{
	connection.addEventHandler(std::tr1::bind(&RaceView::onConnectionEvent,this,std::tr1::placeholders::_1));
	
	addWidget(loader.getRootWidget(), "0px", "0px", "100%", "100%");
}

void RaceView::onConnectionEvent(Connection& connection)
{

}

void RaceView::drawHandler(DrawEvent* event)
{
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
	
	glTranslatef(0, -this->position + 4, 0);
	
	Color(1, 1, 1, 1).apply();
	
	Vector2D position(-trackWidth / 2.0, -5);
	
	Vector2D trackStartSize(trackWidth, trackWidth / trackStart.getSize().getX() * trackStart.getSize().getY());
	
	trackStart.draw(position, trackStartSize);
	position += Vector2D(0, trackStartSize.getY());
	
	Vector2D trackSize(trackWidth, trackWidth / track.getSize().getX() * track.getSize().getY());
	
	for(int i = 0; i < QUARTER_MILE / trackSize.getY() + 10; ++i)
	{
		track.draw(position, trackSize);
		position += Vector2D(0, trackSize.getY());
	}
	
	Texture().bind();
	
	glLineWidth(4.0);
	glBegin(GL_LINES);
		glVertex2f(-trackWidth / 2.0, finishLine);
		glVertex2f(trackWidth / 2.0, finishLine);
	glEnd();
	
	const Protocol::Vehicle& vehicle = connection.getPlayerVehicles().getItem(connection.getActiveVehicleId());
	
	float vehiceLength = vehicle.width / vehicle1.getSize().getX() * vehicle1.getSize().getY();
	
	vehicle1.draw(Vector2D((trackWidth / 4.0) - (vehicle.width / 2.0), this->position - vehiceLength), Vector2D(vehicle.width, vehiceLength));
	
	glPopMatrix();
	
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
}
