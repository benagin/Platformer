#include "KeyEvent.hpp"

KeyEvent::
KeyEvent(Window* _window, Key _key, Mod _mod, Action _action): Event(KeyInput, _window),
	m_key(_key), m_mod(_mod), m_action(_action) {}

Key 
KeyEvent::
GetKey() {
	return m_key;	
}

Mod 
KeyEvent::
GetMod() {
	return m_mod;
}

Action 
KeyEvent::
GetAction() {
	return m_action;
}
