#ifndef INDEXBUFFER_HPP_
#define INDEXBUFFER_HPP_

#include <GL/glew.h>

/// @brief Buffer of index values
class IndexBuffer {

  public:
    ///////////////////////////////////////////////////////////////////////////
    /// @name Constructors
    /// @{
    IndexBuffer(GLuint* _data, size_t _size);
    ~IndexBuffer();
    /// @}
    /// @name Buffer Binding
    /// @{

    void Bind();
    void Unbind();

    /// @}
    /// @name Accessor
    /// @{

    size_t GetSize();

    /// @}
  private:
    GLuint m_handle;  ///< Buffer handle
    size_t m_size;    ///< Size of buffer
};

#endif