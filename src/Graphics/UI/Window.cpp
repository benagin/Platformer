#include "Window.hpp"
#include <iostream>

Window* Window::m_gameWindow = nullptr;

Window::
Window(const std::string& _title, int _width, int _height,
    WindowMode _mode, GLFWmonitor* _monitor): m_width(_width),
  m_height(_height), m_title(_title), m_window(nullptr),
  m_monitor(_monitor) {

    m_window = glfwCreateWindow(m_width, m_height, m_title.c_str(), m_monitor,
        nullptr);

    if(m_gameWindow) {
      std::cout << "Error: Window: Cannot create multiple windows\n";
      exit(1);
    }
    else
      m_gameWindow = this;
  }

Window::
~Window() {
  if(!m_window)
    glfwDestroyWindow(m_window);
}

void
Window::
Init() {
  glfwMakeContextCurrent(m_window);

  glfwSwapInterval(1);

  /* This will be initalize here when we figure out how we wnat to do it.

  // Set cursor position callback.
  glfwSetCursorPosCallback(window, cursor_position_callback);

  // Set mouse button callback.
  glfwSetMouseButtonCallback(window, mouse_button_callback);

  // Set the window resize call back.
  glfwSetFramebufferSizeCallback(window, resize_callback);

  // Set keyboard callback
  glfwSetKeyCallback(window, keyboard_callback);

*/
}

Window*
Window::
Init(WindowMode _mode) {
  /// NOTE(ANDREW): 21/02/2017
  /// This will be loaded from a Config file
  /// and stored in a GameConfig object.
  /// At least, thats what im thinking.

  int height = 480;
  int width = 640;
  GLFWmonitor* monitor = glfwGetPrimaryMonitor();

  switch(_mode) {
    case Windowed:
      monitor = nullptr;
      break;
    case WindowedFull: {
                         const GLFWvidmode* mode = glfwGetVideoMode(monitor);
                         glfwWindowHint(GLFW_RED_BITS, mode->redBits);
                         glfwWindowHint(GLFW_GREEN_BITS, mode->greenBits);
                         glfwWindowHint(GLFW_BLUE_BITS, mode->blueBits);
                         glfwWindowHint(GLFW_REFRESH_RATE, mode->refreshRate);
                         height = mode->height;
                         width = mode->width;
                         break;
                       }
    case FullScreen:
                       // do nothing special
                       break;
  }
  Window* window = new Window("Platformer", width, height, _mode, monitor);
  double x, y;
  glfwGetCursorPos(window->GlfwWindow(), &x, &y);
  window->SetMouseLocation(glm::dvec2(x, y));
  return window;
}

void
Window::
SetTitle(const std::string& _title) {
  glfwSetWindowTitle(m_window, _title.c_str());
  m_title = _title;
}

bool
Window::
ShouldClose() {
  return glfwWindowShouldClose(m_window);
}

void
Window::
SwapBuffers() {
  glfwSwapBuffers(m_window);
}

void
Window::
SetMouseLocation(const glm::dvec2& _pos) {
  m_mouseLocation = _pos;
}

void
Window::
PollEvents() {
  glfwPollEvents();
}

void
Window::
PostQuit() {
  glfwSetWindowShouldClose(m_window, 1);
}
