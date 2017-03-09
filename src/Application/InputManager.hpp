#ifndef INPUT_MANAGER_HPP_
#define INPUT_MANAGER_HPP_
#include <queue>

#include <GLFW/glfw3.h>

#include "Events/Event.hpp"
#include "Events/KeyEvent.hpp"

class Game;

class InputManager {
  public:
    InputManager(Game* _window);

    void Push(Event* _event);
    Event* Top();
    void Pop();
    bool NoInput();
    Window* GetWindow();
    void ToggleKey(unsigned int _key);
    static void Init();
    static InputManager* Get();

    // Input Call backs
    static void KeyCallback(GLFWwindow* _window, int, int, int, int);
    static void MouseButtonCallback(GLFWwindow* _window, int, int, int);
    static void CharCallback(GLFWwindow* _window, unsigned int);
    static void WindowCursorCallback(GLFWwindow* _window, double, double);
    static void WindowScrollCallback(GLFWwindow* _window, double, double);

  private:
    static InputManager* m_instance;
    std::queue<Event*> m_eventQueue;
    Game* m_game;
};


#endif // INPUT_MANAGER_HPP_
