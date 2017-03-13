#ifndef GLDEBUG_HPP_
#define GLDEBUG_HPP_
/// This code is from LearnOpenGL.com
/// This preliminary debugging code.
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <fstream>

GLenum glCheckError_(const char *file, int line);

#define glCheckError() glCheckError_(__FILE__, __LINE__)

std::ostream& operator<< (std::ostream& _out, const glm::vec4& _v);
std::ostream& operator<< (std::ostream& _out, const glm::vec3& _v);
std::ostream& operator<< (std::ostream& _out, const glm::vec2& _v);


#endif