#ifndef EVENT_HPP
#define EVENT_HPP

class Event
{
	public:
		virtual ~Event();
};

class BlurEvent: public Event
{

};

class FocusEvent: public Event
{

};

class ShowEvent: public Event
{

};

class HideEvent: public Event
{

};

#endif // DRAWEVENT_HPP
