#include <memory>
#include <iostream>


#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Application/Game.hpp"
#include "Entities/Entity.hpp"

#include "Graphics/Shader.hpp"
#include "Graphics/Texture2d.hpp"
#include "Graphics/ui/Window.hpp"
#include "Graphics/Font.hpp"


#include "Utilities/FontLoader.hpp"
#include "Utilities/GLDebug.hpp"
#include "Utilities/TextureLoader.hpp"
#include "Utilities/GameConfig.hpp"



float WIDTH;
float HEIGHT;

Window* window;
Font* font;
FontLoader fontLoader;

std::shared_ptr<Shader> shader;
std::shared_ptr<Shader> sprite_shader;
GLuint VBO, VAO;

Texture2d* texture;
TextureLoader loader;

std::shared_ptr<Entity> entity;

GLuint quadVAO;
glm::vec3 loc(0.0,0.0,0.0);
glm::vec2 size(100,100);
Game* game;



/*
static void
error_callback(int error, const char* description) {
  std::cerr << description << std::endl;
}


static void
mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
  // Get the current mouse position.
  double xmouse, ymouse;
  glfwGetCursorPos(window, &xmouse, &ymouse);

  // Get current window size.
  int width, height;
  glfwGetWindowSize(window, &width, &height);

  if(action == GLFW_PRESS) {
    bool shift = (mods & GLFW_MOD_SHIFT) != 0;
    bool ctrl  = (mods & GLFW_MOD_CONTROL) != 0;
    bool alt   = (mods & GLFW_MOD_ALT) != 0;

  }
}


// This function is called when the mouse moves
static void cursor_position_callback(GLFWwindow* window, double xmouse, double ymouse) {
  //int state = glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT);
}


static void keyboard_callback(GLFWwindow* window, int key, int scancode, int action, int mod) {
  if(key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
    glfwSetWindowShouldClose(window, GLFW_TRUE);
  float speed = 1.0;
  if(mod == GLFW_MOD_SHIFT)
    speed *= 3;
  if(action == GLFW_PRESS || action == GLFW_REPEAT) {
    switch(key) {
      case GLFW_KEY_A:
        if(loc.x <= 0)
          loc.x = WIDTH - ( size.x);
        else
          loc.x -= speed;

        break;
      case GLFW_KEY_D:
        if(loc.x >= (WIDTH - ( size.x)))
          loc.x = 0;
        else
          loc.x += speed;
        break;
      case GLFW_KEY_W:
        if(loc.y <= 0)
          loc.y = HEIGHT - ( size.y);
        else
          loc.y -= speed;
        break;
      case GLFW_KEY_S:
        if(loc.y >= HEIGHT - ( size.y))
          loc.y = 0;
        else
          loc.y += speed;
        break;
    }
  }
}


static void resize_callback(GLFWwindow* window, int width, int height) {
  glViewport(0, 0, width, height);
}

static void
init() {
  // Initialize time.
  glfwSetTime(0.0);

  // Set background color.
  glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

  // Enable z-buffer test.
  glEnable(GL_DEPTH_TEST);

  // Enable blending.
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

  // Compile and setup shader.
  // text shaders
  shader = std::make_shared<Shader>("../assets/shaders/text.vs",
      "../assets/shaders/text.frag");

  // sprite shaders
  sprite_shader = std::make_shared<Shader>("../assets/shaders/sprite.vs",
      "../assets/shaders/sprite.frag");

  glm::mat4 p = glm::ortho(0.0f, WIDTH, 0.0f, HEIGHT);
  glm::mat4 projection = glm::ortho(0.0f, WIDTH, HEIGHT, 0.0f, -1.0f, 1.0f);
  shader->AddUniform("projection");
  shader->AddUniform("textColor");

  sprite_shader->AddUniform("model");
  sprite_shader->AddUniform("projection");
  sprite_shader->AddUniform("image");
  sprite_shader->AddUniform("spriteColor");

  shader->Bind();
  shader->SetMatrix4("projection", p);
  shader->Unbind();

  sprite_shader->Bind();
  sprite_shader->SetMatrix4("projection", projection);
  sprite_shader->Unbind();

  texture = loader.LoadPtr("../assets/textures/test_person.png"); // loader() will also work
  if(!texture) {
    std::cout << "Texture is null\n";
  }
  if(!texture->IsLoaded()) {
    std::cout << "Error: Textures: Texture Failed to load" << std::endl;
    exit(1);
  }
  // loading the font
  font = fontLoader.Load("../assets/fonts/Roboto-Light.ttf", 48);

  if(!font) {
    std::cout << "Error: Font: Failed to load font" << std::endl;
    exit(1);
  }

  entity = std::make_shared<Entity>(*texture, loc, size);


  glBindTexture(GL_TEXTURE_2D, 0);

  // Configure VAO/VBO for texture quads.
  glGenVertexArrays(1, &VAO);
  glGenBuffers(1, &VBO);
  glBindVertexArray(VAO);
  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 6 * 4, NULL, GL_DYNAMIC_DRAW);
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), 0);
  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindVertexArray(0);
  glCheckError();

  Renderable::Init();

}
*/

/*
static void RenderText(Font* _font, const std::string& _str, const glm::vec2& _location,
  float _scale, const glm::vec3& _color) {

  shader->Bind();

  glUniform3f(shader->GetUniform("textColor"), _color.x, _color.y, _color.z);
  glActiveTexture(GL_TEXTURE0);
  glBindVertexArray(VAO);

  float x = _location[0];
  for(auto iter = _str.begin(); iter < _str.end(); ++iter) {
    Font::Glyph* glpyh = _font->GetGlyph(*iter);

    if(glpyh) {
      float xpos = x + glpyh->GetBearingX() * _scale;
      float ypos = _location.y - (glpyh->GetHeight() - glpyh->GetBearingY())  * _scale;

      float w = glpyh->GetWidth() * _scale;
      float h = glpyh->GetHeight() * _scale;

      GLfloat vertices[6][4] = {
        {xpos,     ypos + h,   0.0, 0.0},
        {xpos,     ypos,       0.0, 1.0},
        {xpos + w, ypos,       1.0, 1.0},

        {xpos,     ypos + h,   0.0, 0.0},
        {xpos + w, ypos,       1.0, 1.0},
        {xpos + w, ypos + h,   1.0, 0.0}
      };

      glBindTexture(GL_TEXTURE_2D, glpyh->GetTexture());
      glBindBuffer(GL_ARRAY_BUFFER, VBO);
      glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
      glDrawArrays(GL_TRIANGLES, 0, 6);
      glBindBuffer(GL_ARRAY_BUFFER, 0);

      x += (glpyh->GetAdvance() >> 6) * _scale;
    }
    else {
      // TODO(ANDREW): handle this case.
      std::cout << "Invalid Glyph" << *iter << std::endl;
    }
  }

  shader->Unbind();
  glBindVertexArray(0);
  glBindTexture(GL_TEXTURE_2D, 0);
}
*/


// This function is called every frame to draw the scene.
/*
static void render()
{
  // Clear framebuffer.
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  // Get current frame buffer size.

  RenderText(font, "Sample Text", glm::vec2(25, 25), 1.0, glm::vec3(0.3, 0.5, 0.6));
  entity->SetLocation(loc);
  entity->Draw(*sprite_shader);
}
*/


int
main() {


  game = new Game();
  game->Init();
  GameConfig config("../config/game_config.ini");

  // Set error callback.
  // glfwSetErrorCallback(error_callback);

  // window = Window::Init(Windowed);
  // HEIGHT = window->GetHeight();
  // WIDTH = window->GetWidth();
  // window->Init();

  // Initialize GLEW.
  // glew_init();

  // // Set vsync.
  // glfwSwapInterval(1);

  // // Set cursor position callback.
  // glfwSetCursorPosCallback(window->GlfwWindow(), cursor_position_callback);

  // // Set mouse button callback.
  // glfwSetMouseButtonCallback(window->GlfwWindow(), mouse_button_callback);

  // // Set the window resize call back.
  // glfwSetFramebufferSizeCallback(window->GlfwWindow(), resize_callback);

  // // Set keyboard callback
  // glfwSetKeyCallback(window->GlfwWindow(), keyboard_callback);

  // Initialize scene.

  game->Run();
  // game->Close();
  // Quit program.
  delete game;

  glfwTerminate();
  return 0;
}
