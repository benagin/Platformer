#include "Event.hpp"

Event::
Event(EventType _type, Window* _window): m_type(_type), 
	m_bindedWindow(_window) {}

Window*
Event::
GetWindow() {
	return m_bindedWindow;
}

EventType
Event::
GetType() {
	return m_type;
}