#include "Shader.hpp"
#include <glm/gtc/type_ptr.hpp>

Shader::
Shader(const GLchar* _vertPath, const GLchar* _fragPath) {
  std::string vertexCode;
  std::string fragmentCode;
  std::ifstream vShaderFile;
  std::ifstream fShaderFile;

  // Ensures ifstream objects can throw exceptions.
  vShaderFile.exceptions(std::ifstream::badbit);
  fShaderFile.exceptions(std::ifstream::badbit);

  try {
    // Open files.
    vShaderFile.open(_vertPath);
    fShaderFile.open(_fragPath);
    std::stringstream vShaderStream, fShaderStream;

    // Read file's buffer contents into streams.
    vShaderStream << vShaderFile.rdbuf();
    fShaderStream << fShaderFile.rdbuf();

    // Close file handlers.
    vShaderFile.close();
    fShaderFile.close();

    // Convert stream into string
    vertexCode = vShaderStream.str();
    fragmentCode = fShaderStream.str();
  }
  catch (std::ifstream::failure e) {
    std::cout << "Shader failed to read file." << std::endl;
  }

  const GLchar* vShaderCode = vertexCode.c_str();
  const GLchar * fShaderCode = fragmentCode.c_str();

  // Compile shaders.
  GLuint vertex, fragment;
  GLint success;
  GLchar infoLog[512];

  // Vertex Shader.
  vertex = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vertex, 1, &vShaderCode, NULL);
  glCompileShader(vertex);

  // Print compile errors if any.
  glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);

  if(!success) {
    glGetShaderInfoLog(vertex, 512, NULL, infoLog);
    std::cout << "File: " << _vertPath << std::endl;
    std::cout << "Failed to compile vertex shader.\n" << infoLog << std::endl;
  }

  // Fragment Shader.
  fragment = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fragment, 1, &fShaderCode, NULL);
  glCompileShader(fragment);

  // Print compile errors if any.
  glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);

  if(!success) {
    glGetShaderInfoLog(fragment, 512, NULL, infoLog);
    std::cout << "File: " << _fragPath << std::endl;
    std::cout << "Failed to compile fragment shader.\n" << infoLog << std::endl;
  }

  // Shader Program.
  m_program = glCreateProgram();
  glAttachShader(m_program, vertex);
  glAttachShader(m_program, fragment);
  glLinkProgram(m_program);

  // Print linking errors if any
  glGetProgramiv(m_program, GL_LINK_STATUS, &success);

  if(!success) {
    glGetProgramInfoLog(m_program, 512, NULL, infoLog);
    std::cout << "Shader failed to link.\n" << infoLog << std::endl;
  }

  // Delete the shaders as they're linked into our program now and no longer
  // necessary.
  glDeleteShader(vertex);
  glDeleteShader(fragment);
}


void
Shader::
Bind() {
  glUseProgram(m_program);
}


void
Shader::
Unbind() {
  glUseProgram(0);
}


GLuint
Shader::
GetAttribute(const std::string& _att) {
  auto loc = m_attributes.find(_att);

  if(loc == m_attributes.end()) {
    std::cout << "Error: '" << _att << "' is not a attribute variable." << std::endl;

    return -1;
  }

  return loc->second;
}


GLuint
Shader::
AddAttribute(const std::string& _att) {
  GLuint t = glGetAttribLocation(m_program, _att.c_str());
  m_attributes.emplace(_att, t);

  return t;
}


GLuint
Shader::
GetUniform(const std::string& _att) {
  auto loc = m_uniforms.find(_att);

  if(loc == m_uniforms.end()) {
    std::cout << "Error: " << _att << " is not a uniform variable." << std::endl;

    return -1;
  }

  return loc->second;
}


GLuint
Shader::
AddUniform(const std::string& _att) {
  GLuint t = glGetUniformLocation(m_program, _att.c_str());
  m_uniforms.emplace(_att, t);

  return t;
}

void 
Shader::
SetFloat(const std::string& _att, float _f) {
  glUniform1f(GetUniform(_att), _f);
}

void 
Shader::
SetInteger(const std::string& _att, int _i) {
  glUniform1i(GetUniform(_att), _i);
}


void 
Shader::
SetVector2f(const std::string& _att, float _f1, float _f2) {
  glUniform2f(GetUniform(_att), _f1, _f2);
}

void 
Shader::
SetVector3f(const std::string& _att, float _f1, float _f2, float _f3) {
  glUniform3f(GetUniform(_att), _f1, _f2, _f3);
}

void 
Shader::
SetVector4f(const std::string& _att, float _f1, float _f2, float _f3, float _f4) {
  glUniform4f(GetUniform(_att), _f1, _f2, _f3, _f4);
}


void 
Shader::
SetVector2f(const std::string& _att, const glm::vec2& _v) {
  SetVector2f(_att, _v.x, _v.y);
}

void 
Shader::
SetVector3f(const std::string& _att, const glm::vec3& _v) {
  SetVector3f(_att, _v.x, _v.y, _v.z);
}

void 
Shader::
SetVector4f(const std::string& _att, const glm::vec4& _v) {
  SetVector4f(_att, _v.x, _v.y, _v.z, _v.w);
}

void
Shader::
SetMatrix4(const std::string& _att, const glm::mat4& _mat) {
  glUniformMatrix4fv(GetUniform(_att), 1, GL_FALSE, glm::value_ptr(_mat));
}

