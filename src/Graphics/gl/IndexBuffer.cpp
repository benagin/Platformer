#include "IndexBuffer.hpp"

IndexBuffer::
IndexBuffer(GLuint* _data, size_t _size) {
  m_size = _size;
  glGenBuffers(1, &m_handle);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_handle);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_size * sizeof(GLuint), _data, GL_STATIC_DRAW);
}

IndexBuffer::
~IndexBuffer() {
  glDeleteBuffers(1, &m_handle);
}

void
IndexBuffer::
Bind() {
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_handle);
}

void
IndexBuffer::
Unbind() {
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

size_t
IndexBuffer::
GetSize() {
  return m_size;
}
