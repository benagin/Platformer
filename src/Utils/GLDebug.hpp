#ifndef GLDEBUG_HPP_
#define GLDEBUG_HPP_
/// This code is from LearnOpenGL.com
/// This preliminary debugging code.
#include <GL/glew.h>

GLenum glCheckError_(const char *file, int line);

#define glCheckError() glCheckError_(__FILE__, __LINE__)

#endif