#include "Game.hpp"
#include <iostream>

#include "Events/MouseClickEvent.hpp"
#include "Events/MouseButtonEvent.hpp"
#include "Events/MouseMovementEvent.hpp"
#include "Events/WindowResizeEvent.hpp"
#include "Events/WindowScrollEvent.hpp"

Game::
Game(): m_window(nullptr), m_state(Menu), m_running(false),
  m_inputManager(nullptr) {}


Game::
~Game() {}


void
Game::
Init() {
  Game::InitGL();
  m_window = Window::Init(Windowed);
  m_window->Init();
  Game::InitGlew();
  m_resources = Resources::Init("../assets/game.rsc");
  m_inputManager = new InputManager(this);
  m_inputManager->Init();
  m_running = true;

  m_camera.SetInitDistance(2.);

  glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
  glEnable(GL_DEPTH_TEST);
}


void
Game::
Update() {
  ProcessInput();
}


void
Game::
Render() {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  // Reset camera aspect if window size changes.
  int width, height;
  glfwGetFramebufferSize(m_window->GlfwWindow(), &width, &height);
  m_camera.SetAspect((float) width/(float) height);

  // Matrix stacks
  MatrixStack P;
  MatrixStack MV;

  // Apply camera transforms.
  P.pushMatrix();
  m_camera.ApplyProjectionMatrix(P);
  MV.pushMatrix();
  m_camera.ApplyViewMatrix(MV);

  P.popMatrix();
  MV.popMatrix();
}


void
Game::
InitGL() {
 if(!glfwInit()) {
    exit(1);
  }
  // NOTE(ANDREW): 17/02/2017
  // This is setting the version of open gl that we are using
  // In this case it is being set to version 3.3
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
}


void
Game::
InitGlew() {
   glewExperimental = true;
  if(glewInit() != GLEW_OK) {
    std::cerr << "Failed to initialize GLEW" << std::endl;
    exit(1);
  }
  glGetError();

  std::cout << "OpenGL version: " << glGetString(GL_VERSION) << std::endl;
  std::cout << "GLSL version: " << glGetString(GL_SHADING_LANGUAGE_VERSION)
    << std::endl;
}


void
Game::
Run() {
  while(!m_window->ShouldClose()) {
    Update();
    Render();
    m_window->PollEvents();
  }
}


void
Game::
ToggleKey(unsigned int _key) {
  m_keys[_key] = !m_keys[_key];
}


void
Game::
SetCursor(const glm::dvec2& _pos) {
  m_window->SetMouseLocation(_pos);
}


void
Game::
ProcessInput() {
  if(m_inputManager->NoInput())
    return;

  Event* event = m_inputManager->Top();
  m_inputManager->Pop();

  switch(event->GetType()) {
    case KeyInput: {
      auto keyEvent = (KeyEvent*) event;
      if(keyEvent->GetKey() == Key_ESC && keyEvent->GetAction() == Action_Press) {
        // Maybe have an are you sure you want to quit message.
        QuitGame();
      }
    } break;
    case MouseButton: {
      auto mouseEvent = (MouseClickEvent*) event;
      auto loc = mouseEvent->Location();
      std::cout << "Mouse Clicked at: " <<  loc.x << ", " << loc.y << std::endl;
      if(m_state == Menu) {

      }
    } break;
    case MouseMovement: {
      auto mouseEvent = (MouseMovementEvent*) event;
      m_window->SetMouseLocation(mouseEvent->Location());
    } break;
    case WindowResize: {

    } break;
    case WindowScroll: {

    } break;
  }
  delete event;
}


void
Game::
QuitGame() {
  m_window->PostQuit();
}
