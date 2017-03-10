#ifndef VERTEXBUFFER_HPP_
#define VERTEXBUFFER_HPP_
#include <GL/glew.h>

/// @brief The usage type of this buffer
enum Usage : unsigned {
  DynamicDraw,
  StaticDraw
};


/// @brief A vertex buffer wrapper.
class VertexBuffer {

  public:
    ///////////////////////////////////////////////////////////////////////////
    /// @name Constructors
    /// @{

    VertexBuffer(size_t _size, Usage _usage);
    VertexBuffer(size_t _size, void* _data, Usage _usage);
    ~VertexBuffer();

    /// @}
    /// @name Buffer Access
    /// @{

    void Resize(size_t _size);
    void SetData(void* _data, size_t _size);
    void* Pointer();
    void Release();

    /// @}
    /// @name Buffer binding.
    /// @{

    void Bind();
    void Unbind();

    bool IsBound();
    /// @}
  private:
    GLuint m_handle;
    size_t m_size;
    Usage m_usage;
    bool m_bounded;
    bool m_filled;
};


#endif