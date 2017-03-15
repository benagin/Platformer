#ifndef VERTEXARRAY_HPP_
#define VERTEXARRAY_HPP_

#include <vector>
#include "VertexBuffer.hpp"

/// @brief Vertex Array Object
class VertexArray {

  public:
    ///////////////////////////////////////////////////////////////////////////
    /// @name Constructors
    /// @{

    VertexArray();
    ~VertexArray();

    /// @} 
    /// @name Modifiers
    /// @{

    /// @brief Adds a buffer to the buffer array
    /// @param _buffer Vertex Buffer being added.
    void AddBuffer(VertexBuffer* _buffer);

    /// @brief Draws the contents of the current buffers
    /// @param _size Size of the buffer being drawn
    void Draw(size_t _size);

    /// @brief Retrieves a buffer from the Buffer Array
    /// @param _i index of the buffer.
    VertexBuffer* GetBuffer(size_t _i = 0);
    
    /// @} 
    /// @name Buffer Minding
    /// @{
      
    /// @brief Binds the vertex array
    void Bind();

    /// @brief Unbinds the vertex array
    void Unbind();

    /// @}
  private:
    GLuint m_handle;   ///< Buffer Handle
    std::vector<VertexBuffer*> m_buffers; ///< Buffers
};

#endif