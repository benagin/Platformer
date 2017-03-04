#include <cstdlib>
#include <iostream>

#include "Game.hpp"
#include "InputManager.hpp"

#include "Events/MouseClickEvent.hpp"
#include "Events/MouseButtonEvent.hpp"
#include "Events/MouseMovementEvent.hpp"
#include "Events/WindowResizeEvent.hpp"
#include "Events/WindowScrollEvent.hpp"

InputManager* InputManager::m_instance = nullptr;

InputManager::
InputManager(Game* _game): m_game(_game) {
  if(m_instance) {
    std::cout << "Error: Cannot Initialize mulitple InputManagers" << std::endl;
    exit(1);
  }

  m_instance = this;
}

Window*
InputManager::
GetWindow() {
  return m_game->GetWindow();
}

void
InputManager::
Push(Event* _event) {
	m_eventQueue.push(_event);
}


Event*
InputManager::
Top() {
  return m_eventQueue.front();
}

void
InputManager::
Pop() {
  m_eventQueue.pop();
}

bool
InputManager::
NoInput() {
  return m_eventQueue.empty();
}



void
InputManager::
Init() {
  GLFWwindow* window = InputManager::Get()->GetWindow()->GlfwWindow();
  glfwSetKeyCallback(window, InputManager::KeyCallback);
  glfwSetCharCallback(window, InputManager::CharCallback);
  glfwSetMouseButtonCallback(window, InputManager::MouseButtonCallback);
  glfwSetCursorPosCallback(window, InputManager::WindowCursorCallback);
  glfwSetScrollCallback(window, InputManager::WindowCursorCallback);
  //glfwSetWindowSizeCallback(window, InputManager::)
}


InputManager*
InputManager::
Get() {
	return m_instance;
}



// Input Call backs
void
InputManager::
KeyCallback(GLFWwindow* _window, int _key, int _scancode, int _action, int _mods) {
  InputManager* manager = InputManager::Get();
  std::cout << "Key Call back " << _key << std::endl;  
  KeyEvent* input = new KeyEvent(manager->GetWindow(), 
    static_cast<Key>(_key),
    static_cast<Mod>(_mods),
    static_cast<Action>(_action));
  manager->Push(input);
}

void 
InputManager::
ToggleKey(unsigned int _key) {
  m_game->ToggleKey(_key);
}


void
InputManager::
MouseButtonCallback(GLFWwindow* _window, int _button, int _action, int _mods) {
  InputManager* manager = InputManager::Get();
  const auto& loc = manager->GetWindow()->GetMouseLocation();
  MouseClickEvent* event = new MouseClickEvent(
    manager->GetWindow(), 
    static_cast<Mod>(_mods),
    static_cast<Action>(_action),
    loc);
  manager->Push(event);
}


void
InputManager::
CharCallback(GLFWwindow* _window, unsigned int _codepoint) {
  InputManager* manager = InputManager::Get();
  manager->ToggleKey(_codepoint);
}


void
InputManager::
WindowCursorCallback(GLFWwindow* _window, double _xpos, double _ypos) {
  InputManager* manager = InputManager::Get();
  MouseMovementEvent* event = new MouseMovementEvent(manager->GetWindow(), _xpos, _ypos);
  manager->Push(event);
}


void
InputManager::
WindowScrollCallback(GLFWwindow* _window, double _xoffset, double _yoffset) {
}