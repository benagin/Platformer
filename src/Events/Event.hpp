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