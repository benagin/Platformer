#ifndef SHADER_H_
#define SHADER_H_

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <map>

#include <glm/glm.hpp>
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

    void SetMatrix4(const std::string& _att, const glm::mat4& _m);

    void SetFloat(const std::string& _att, float _f);
    void SetInteger(const std::string& _att, int _i);

    void SetVector2f(const std::string& _att, float _f1, float _f2);
    void SetVector3f(const std::string& _att, float _f1, float _f2, float _f3);
    void SetVector4f(const std::string& _att, float _f1, float _f2, float _f3, float _f4);

    void SetVector2f(const std::string& _att, const glm::vec2& _v);
    void SetVector3f(const std::string& _att, const glm::vec3& _v);
    void SetVector4f(const std::string& _att, const glm::vec4& _v);



  private:
    GLuint m_program; ///< The program ID.

    std::map<std::string, GLuint> m_attributes;
    std::map<std::string, GLuint> m_uniforms;
};

#endif
