#include <iostream>

#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include "FTLoader.hpp"


GLFWwindow* window;


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
  /*
  Shader shader("assets/shaders/text.vs", "assets/shaders/text.frag");
  glm::mat4 projection = glm::orth(0.0f, 800.0f, 0.0f, 600.0f);
  shader.Use();
  glUniformMatrix4fv(glGetUniformLocation(shader.Program, "projection"), 1,
      GL_FALSE, glm::value_ptr(projection));
  */

  // Setup FreeType for redering text.
  FTLoader* ftl = new FTLoader();

  glBindTexture(GL_TEXTURE_2D, 0);

  delete ftl;

  // Configure VAO/VBO for texture quads.
  /*
  glGenVertexArrays(1, &VAO);
  glGenBuffers(1, &VBO);
  glBindVertexArray(VAO);
  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 6 * 4, NULL, GL_DYNAMIC_DRAW);
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), 0);
  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindVertexArray(0);
  */
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
}


int
main() {
  // Set error callback.
  glfwSetErrorCallback(error_callback);

  // Initialize the library.
  if(!glfwInit()) {
    return -1;
  }

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

  // Quit program.
  glfwDestroyWindow(window);
  glfwTerminate();

  return 0;
}
