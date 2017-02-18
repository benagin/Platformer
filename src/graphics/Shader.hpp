#ifndef SHADER_H_
#define SHADER_H_

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <map>

#include <GL/glew.h>

class Shader {
  public:
    // the program ID
    GLuint program; 
    // Construct reads and builds the shader 
    Shader(const GLchar* _vertexPath, const GLchar* _fragPath);
    // uses the program
    void bind();
    void unbind();

    GLuint set_attribute(const std::string& _att);
  
    GLuint get_attribute(const std::string& _att);
  
    GLuint set_uniform(const std::string& _att);
  
    GLuint get_uniform(const std::string& _att);
  private:
    std::map<std::string, GLuint> attr_map;
    std::map<std::string, GLuint> uniform_map;
};

#endif
