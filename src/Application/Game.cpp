#include "Game.hpp"
#include <iostream>
#include <glm/gtc/matrix_transform.hpp>

#include "Events/MouseClickEvent.hpp"
#include "Events/MouseButtonEvent.hpp"
#include "Events/MouseMovementEvent.hpp"
#include "Events/WindowResizeEvent.hpp"
#include "Events/WindowScrollEvent.hpp"

#include "Utilities/GLDebug.hpp"


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
  glBlendFunc(GL_DST_ALPHA, GL_ONE_MINUS_DST_ALPHA); 
  glClearColor(0.7f,0.7f,0.8f,1.0f); 
  m_resources = Resources::Init("../assets/XML/Resources/resources.xml");
  m_inputManager = new InputManager(this);
  m_inputManager->Init();
  m_running = true;
  
  // m_camera = new Camera(glm::ortho(-16.0f, 16.0f, -9.0f, 
  //   9.0f, -1.0f, 1.0f));
    
  m_renderer = new ForwardRenderer2D(
    glm::ivec2(
      m_window->GetWidth(),
      m_window->GetHeight()
    )
  );

  m_renderer->SetCamera(&m_camera);
  m_renderer->Init();
  glCheckError();
  

  Entity* temp = new Entity(
    m_resources->GetTexture("person"),
    glm::vec3(10,10,0),
    glm::vec2(100,100)); 
  m_entities.push_back(temp);

  temp = new Entity(
    m_resources->GetTexture("person"),
    glm::vec3(10,150,0),
    glm::vec2(100,100));
  m_entities.push_back(temp);

  m_camera.SetInitDistance(2.);

  // glEnable(GL_DEPTH_TEST);
  glCheckError();
}


void
Game::
Update() {
  m_window->PollEvents();
  ProcessInput();
  glClear(GL_COLOR_BUFFER_BIT);
}


void
Game::
Render() {
  // m_renderer->Begin();
  for(auto e : m_entities) {
    m_renderer->Submit(e);
  }
  // m_renderer->Present();
  // m_renderer->End();

  // Reset camera aspect if window size changes.
  m_camera.SetAspect((float) m_window->GetWidth()/(float) m_window->GetHeight());

  switch(m_state) {
      case Menu:
        RenderMenu();
        break;

      case Gameplay:
        RenderGame();
        break;

      case GameOver:
        RenderGameOver();
        break;
    }
}


void
Game::
RenderMenu() {
  // Draw menu GUI.
  //m_menu.Draw(s);
}


void
Game::
RenderGame() {
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
RenderGameOver() {

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
  // glEnable(GL_DEPTH_TEST);

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

    m_window->SwapBuffers();
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
