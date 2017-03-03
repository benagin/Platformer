#ifndef MOUSE_MOVEMENT_EVENT_HPP_
#define MOUSE_MOVEMENT_EVENT_HPP_

#include "Event.hpp"
#include <glm/glm.hpp>

class Window;
class MouseMovementEvent : public Event {
public:
	MouseMovementEvent(Window* _window, double _xPos, double _yPos);
	glm::dvec2 Location();
private:
	glm::dvec2 m_location;
};


#endif // MOUSE_MOVEMENT_EVENT_HPP_
