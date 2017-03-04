#ifndef EVENT_HPP_
#define EVENT_HPP_
#include "Graphics/UI/Window.hpp"

enum EventType {
	KeyInput = 0,
	MouseButton,
	MouseMovement,
	WindowResize,
	WindowScroll
};

enum Mod {
	Mod_None = 0x0,
	Mod_Shift = GLFW_MOD_SHIFT,
	Mod_Control = GLFW_MOD_CONTROL,
	Mod_Alt = GLFW_MOD_ALT,
	Mod_Super = GLFW_MOD_SUPER
};

enum Action {
	Action_Release = GLFW_RELEASE,
	Action_Press = GLFW_PRESS,
	Action_Repeat = GLFW_REPEAT
};


class Event {
public:
	Event(EventType _type, Window* _window);
	Window* GetWindow();
	EventType GetType();
private:
	EventType m_type;
	Window* m_bindedWindow;
};

#endif