#include "MouseMovementEvent.hpp"

MouseMovementEvent::
MouseMovementEvent(Window* _window, double _xPos, double _yPos): 
  Event(MouseMovement, _window), m_location(_xPos, _yPos) {}

glm::dvec2
MouseMovementEvent::
Location() {
  return m_location;
}