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

    /// @brief Vertex Buffer Constructor.
    /// @param _size Size of the buffer
    /// @param _usage How this buffer is to be used.
    VertexBuffer(size_t _size, Usage _usage);
    
    /// @brief Vertex Buffer Constructor for adding data
    /// @param _size Size of the buffer.
    /// @param _data Data of the buffer.
    /// @param _usage How this buffer is to be used.
    VertexBuffer(size_t _size, void* _data, Usage _usage);

    ~VertexBuffer();

    /// @}
    /// @name Buffer Access
    /// @{

    /// @brief Resize the buffer
    /// @param _size Size of the new buffer
    void Resize(size_t _size);
    
    /// @brief Set the data of the buffer
    /// @param _data Data of the buffer
    /// @param _size Size of data in bytes.
    void SetData(void* _data, size_t _size);
    
    /// @brief Maps the buffer
    void* Pointer();
    
    /// @brief Unmaps the buffer
    void Release();

    /// @}
    /// @name Buffer binding.
    /// @{

    /// @brief Binds the buffer
    void Bind();
    
    /// @brief Unbinds the buffer
    void Unbind();

    /// @brief Returns whether the buffer has been bound.
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