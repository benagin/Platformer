#include "Utils/GLDebug.hpp"
#include "VertexBuffer.hpp"

/// @brief a function for converting between Usage and GLenum.
GLenum ToGlUsage(unsigned _enum) {
  switch(_enum) {
    case DynamicDraw:
      return GL_DYNAMIC_DRAW;
    case StaticDraw:
      return GL_STATIC_DRAW;
  }
  return GL_DYNAMIC_DRAW;
}

VertexBuffer::
VertexBuffer(size_t _size, Usage _usage) {
  glGenBuffers(1, &m_handle);
  m_size = 0;
  m_usage = _usage;
  m_bounded = false;
  m_filled = false;
}

VertexBuffer::
VertexBuffer(size_t _size, void* _data, Usage _usage) {
  glGenBuffers(1, &m_handle);
  m_size = 0;
  m_usage = _usage;
  m_bounded = false;
  m_filled = false;
  SetData(_data, _size);
}

VertexBuffer::
~VertexBuffer() {
  glDeleteBuffers(1, &m_handle);
}

void
VertexBuffer::
Resize(size_t _size) {
  m_size = _size;
  glBindBuffer(GL_ARRAY_BUFFER, m_handle);
  glBufferData(GL_ARRAY_BUFFER, m_size, nullptr, ToGlUsage(m_usage));
  glCheckError();
}

void
VertexBuffer::
SetData(void* _data, size_t _size) {
  m_size = _size;
  glBindBuffer(GL_ARRAY_BUFFER, m_handle);
  glBufferData(GL_ARRAY_BUFFER, m_size, nullptr, ToGlUsage(m_usage));
  glCheckError();
  m_filled = true;
}

void*
VertexBuffer::
Pointer() {
  glBindBuffer(GL_ARRAY_BUFFER, m_handle);
  void* result = glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);
  return result;
}

void
VertexBuffer::
Release() {
  glBindBuffer(GL_ARRAY_BUFFER, m_handle);
  glUnmapBuffer(GL_ARRAY_BUFFER);
}

void
VertexBuffer::
Bind() {
  glBindBuffer(GL_ARRAY_BUFFER, m_handle);
  m_bounded = true;
}

void
VertexBuffer::
Unbind() {
  glBindBuffer(GL_ARRAY_BUFFER, 0);
  m_bounded = false;
}

bool
VertexBuffer::
IsBound() {
  return m_bounded;
}
