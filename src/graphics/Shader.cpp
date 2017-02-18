#include "Shader.hpp"
using namespace std;

Shader::Shader(const GLchar* vertexPath, const GLchar* fragmentPath) {
  std::string vertexCode;
  std::string fragmentCode;
  std::ifstream vShaderFile;
  std::ifstream fShaderFile;
  // ensures ifstream objects can throw exceptions:
  vShaderFile.exceptions (std::ifstream::badbit);
  fShaderFile.exceptions (std::ifstream::badbit);
  try
  {
      // Open files
      vShaderFile.open(vertexPath);
      fShaderFile.open(fragmentPath);
      std::stringstream vShaderStream, fShaderStream;
      // Read file's buffer contents into streams
      vShaderStream << vShaderFile.rdbuf();
      fShaderStream << fShaderFile.rdbuf();
      // close file handlers
      vShaderFile.close();
      fShaderFile.close();
      // Convert stream into string
      vertexCode = vShaderStream.str();
      fragmentCode = fShaderStream.str();
  }
  catch (std::ifstream::failure e)
  {
      std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
  }
  const GLchar* vShaderCode = vertexCode.c_str();
  const GLchar * fShaderCode = fragmentCode.c_str();
  // 2. Compile shaders
  GLuint vertex, fragment;
  GLint success;
  GLchar infoLog[512];
  // Vertex Shader
  vertex = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vertex, 1, &vShaderCode, NULL);
  glCompileShader(vertex);
  // Print compile errors if any
  glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
  if (!success)
  {
      glGetShaderInfoLog(vertex, 512, NULL, infoLog);
      std::cout << "File: " << vertexPath << std::endl;
      std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
  }
  // Fragment Shader
  fragment = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fragment, 1, &fShaderCode, NULL);
  glCompileShader(fragment);
  // Print compile errors if any
  glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
  if (!success)
  {
      glGetShaderInfoLog(fragment, 512, NULL, infoLog);
      std::cout << "File: " << fragmentPath << std::endl;
      std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
  }
  // Shader Program
  this->program = glCreateProgram();
  glAttachShader(this->program, vertex);
  glAttachShader(this->program, fragment);
  glLinkProgram(this->program);
  // Print linking errors if any
  glGetProgramiv(this->program, GL_LINK_STATUS, &success);
  if (!success)
  {
      glGetProgramInfoLog(this->program, 512, NULL, infoLog);
      std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
  }
  // Delete the shaders as they're linked into our program now and no longer necessery
  glDeleteShader(vertex);
  glDeleteShader(fragment);

}

void Shader::bind() {
  glUseProgram(program);
}   

void Shader::unbind() {
    glUseProgram(0);
}

GLuint Shader::set_attribute(const std::string& _att) {
    GLuint t = glGetAttribLocation(program, _att.c_str());
    attr_map.emplace(_att, t);
    return t;
}

GLuint Shader::get_attribute(const std::string& _att) {
    auto loc = attr_map.find(_att);
    if(loc == attr_map.end()) {
        std::cout << "Error: " << _att << " is not a uniform" << endl;
        return -1; 
    }
    return loc->second;
}

GLuint Shader::set_uniform(const std::string& _att) {
    GLuint t = glGetUniformLocation(program, _att.c_str());
    uniform_map.emplace(_att, t);
    return t;
}

GLuint Shader::get_uniform(const std::string& _att) {
    auto loc = uniform_map.find(_att);
    if(loc == uniform_map.end()) {
        std::cout << "Error: " << _att << " is not a uniform" << endl;
        return -1; 
    }
    return loc->second;
}
