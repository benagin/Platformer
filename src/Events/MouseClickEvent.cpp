#include "MouseClickEvent.hpp"

MouseClickEvent::
MouseClickEvent(Window* _window, Mod _mod, Action _action, const glm::dvec2& _loc):
  Event(MouseButton, _window), m_location(_loc), m_mod(_mod), m_action(_action) {}

glm::dvec2
MouseClickEvent::
Location() {
  return m_location;
}

Mod
MouseClickEvent::
GetMod() {
  return m_mod;
}

Action
MouseClickEvent::
GetAction() {
 return m_action;
}
