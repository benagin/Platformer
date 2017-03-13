#include "VertexArray.hpp"
#include <iostream>

VertexArray::
VertexArray() {
  glGenVertexArrays(1, &m_handle);
}

VertexArray::
~VertexArray() {

}

void
VertexArray::
AddBuffer(VertexBuffer* _buffer) {
  m_buffers.push_back(_buffer);
}

VertexBuffer*
VertexArray::
GetBuffer(size_t _i) {
  if(_i >= m_buffers.size() && _i >= 0)
    return nullptr;
  return m_buffers[_i];
}

void
VertexArray::
Bind() {
  glBindVertexArray(m_handle);
}

void
VertexArray::
Unbind() {
  glBindVertexArray(0);
}

void
VertexArray::
Draw(size_t _size) {
  glDrawElements(GL_TRIANGLES, _size, GL_UNSIGNED_INT, nullptr);
}