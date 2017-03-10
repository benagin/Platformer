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

    void AddBuffer(VertexBuffer* _buffer);
    void Draw(size_t _size);

    VertexBuffer* GetBuffer(size_t _i = 0);
    
    /// @} 
    /// @name Buffer Minding
    /// @{
      
    void Bind();
    void Unbind();

    /// @}
  private:
    GLuint m_handle;   ///< Buffer Handle
    std::vector<VertexBuffer*> m_buffers; ///< Buffers

};

#endif