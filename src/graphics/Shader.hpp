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

    // Construct reads and builds the shader
    Shader(const GLchar* _vertexPath, const GLchar* _fragPath);

    // Bind and unbind the program.
    void Bind();

    void Unbind();

    GLuint GetAttribute(const std::string& _att);

    GLuint AddAttribute(const std::string& _att);

    GLuint AddUniform(const std::string& _att);

    GLuint GetUniform(const std::string& _att);

    GLuint GetProgram() const { return m_program; }

  private:
    GLuint m_program; ///< The program ID.

    std::map<std::string, GLuint> m_attributes;
    std::map<std::string, GLuint> m_uniforms;
};

#endif
