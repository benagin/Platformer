#include <iostream>

#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <memory>

#include "utils/FTLoader.hpp"
#include "utils/Font.hpp"
#include "utils/GLDebug.hpp"
#include "graphics/Shader.hpp"

GLFWwindow* window;
Font* font;
FTLoader* font_loader;

std::shared_ptr<Shader> shader;
GLuint VBO, VAO;


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

  /*
  if(action == GLFW_PRESS) {
    bool shift = (mods & GLFW_MOD_SHIFT) != 0;
    bool ctrl  = (mods & GLFW_MOD_CONTROL) != 0;
    bool alt   = (mods & GLFW_MOD_ALT) != 0;

  }
  */
}


// This function is called when the mouse moves
static void
cursor_position_callback(GLFWwindow* window, double xmouse, double ymouse) {
  //int state = glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT);
}


static void keyboard_callback(GLFWwindow* window, int key, int scancode, int action, int mod) {
  if(key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
    glfwSetWindowShouldClose(window, GLFW_TRUE);
}


static void
resize_callback(GLFWwindow* window, int width, int height)
{
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
  shader = std::make_shared<Shader>("../assets/shaders/text.vs",
      "../assets/shaders/text.frag");

  glm::mat4 projection = glm::ortho(0.0f, 800.0f, 0.0f, 600.0f);
  shader->AddUniform("projection");
  shader->AddUniform("textColor");

  shader->Bind();

  glUniformMatrix4fv(shader->GetUniform("projection"), 1,
      GL_FALSE, glm::value_ptr(projection));
  shader->Unbind();

  font = Font::LoadFont("../assets/fonts/Roboto-Light.ttf", 48);
  if(!font) {
    std::cout << "Error: Font: Failed to load font" << std::endl;
    exit(1);
  }

  // Setup FreeType for redering text.
  font_loader = new FTLoader();

  glBindTexture(GL_TEXTURE_2D, 0);

  //delete ftl;

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
}

static void RenderTextFTLoader(FTLoader* _font, const std::string& _str, const glm::vec2& _location,
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
      float ypos = _location.y * _scale;

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

      x += (glpyh->GetAdvance() >> 6);
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

static void RenderTextFont(Font* _font, const std::string& _str, const glm::vec2& _location,
  float _scale, const glm::vec3& _color) {
  shader->Bind();
  glUniform3f(shader->GetUniform("textColor"), _color.x, _color.y, _color.z);
  glActiveTexture(GL_TEXTURE0);
  glBindVertexArray(VAO);

  float x = _location.x;
  for(auto iter = _str.begin(); iter < _str.end(); ++iter) {
    Font::Glyph* glpyh = _font->GetGlyph(*iter);
    if(glpyh) {

      if(*iter == ' ') {
        x += (glpyh->GetAdvance() >> 6);
        continue;
      }

      float xpos = x * _scale;// + glpyh->GetStride();
      float ypos = _location.y + _font->GetYAdvance() * _scale;
      float w = glpyh->GetWidth() * _scale;;
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

      x += (glpyh->GetAdvance() >> 6);
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

// This function is called every frame to draw the scene.
static void render()
{
  // Clear framebuffer.
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  // Get current frame buffer size.
  int width, height;

  glfwGetFramebufferSize(window, &width, &height);

  //float aspect = width/(float)height;
  RenderTextFTLoader(font_loader, "This is a sample Text",
      glm::vec2(25, 25), 1.0f, glm::vec3(0.2, 0.7, 0.1));

  RenderTextFont(font, "This is a sample Text", glm::vec2(540, 570), 0.5f,
      glm::vec3(0.2, 0.3, 0.7));
}


int
main() {
  // Set error callback.
  glfwSetErrorCallback(error_callback);

  // Initialize the library.
  if(!glfwInit()) {
    return -1;
  }
  // NOTE(ANDREW): 17/02/2017
  // This is setting the version of open gl that we are using
  // In this case it is being set to version 3.3
  // This will be moved out of main at some point.
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

  // Create a windowed mode window and its OpenGL context.
  window = glfwCreateWindow(640, 480, "Game", NULL, NULL);

  if(!window) {
    glfwTerminate();
    return -1;
  }

  // Make the window's context current.
  glfwMakeContextCurrent(window);

  // Initialize GLEW.
  glewExperimental = true;
  if(glewInit() != GLEW_OK) {
    std::cerr << "Failed to initialize GLEW" << std::endl;
    return -1;
  }

  glGetError();

  std::cout << "OpenGL version: " << glGetString(GL_VERSION) << std::endl;
  std::cout << "GLSL version: " << glGetString(GL_SHADING_LANGUAGE_VERSION)
    << std::endl;

  // Set vsync.
  glfwSwapInterval(1);

  // Set cursor position callback.
  glfwSetCursorPosCallback(window, cursor_position_callback);

  // Set mouse button callback.
  glfwSetMouseButtonCallback(window, mouse_button_callback);

  // Set the window resize call back.
  glfwSetFramebufferSizeCallback(window, resize_callback);

  // Set keyboard callback
  glfwSetKeyCallback(window, keyboard_callback);

  // Initialize scene.
  init();

  // Loop until the user closes the window.
  while(!glfwWindowShouldClose(window)) {
    // Render scene.
    render();

    // Swap front and back buffers.
    glfwSwapBuffers(window);

    // Poll for and process events.
    glfwPollEvents();
  }

  delete font;
  delete font_loader;

  // Quit program.
  glfwDestroyWindow(window);
  glfwTerminate();

  return 0;
}
