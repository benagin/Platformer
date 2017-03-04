#ifndef MOUSE_CLICK_EVENT_HPP_
#define MOUSE_CLICK_EVENT_HPP_

#include <glm/glm.hpp>
#include "Event.hpp"

class MouseClickEvent : public Event {
public:
	MouseClickEvent(Window* _window, Mod _mod, Action _action, const glm::dvec2& _loc);
	glm::dvec2 Location();
	Mod GetMod();
	Action GetAction();
private:
	glm::dvec2 m_location;
	Mod m_mod;
	Action m_action;
};


#endif // MOUSE_CLICK_EVENT_HPP_
