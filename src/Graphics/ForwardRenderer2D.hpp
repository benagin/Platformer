#ifndef FORWARDRENDERER2D_HPP_
#define FORWARDRENDERER2D_HPP_

#include <glm/glm.hpp>
#include "Graphics/Camera.hpp"
#include "Graphics/Font.hpp"
#include "Graphics/gl/VertexArray.hpp"
#include "Graphics/gl/VertexArray.hpp"
#include "Graphics/gl/IndexBuffer.hpp"
#include "Graphics/Renderable2D.hpp"
#include "Graphics/Texture2D.hpp"
#include "Application/Resources.hpp"

#define MAX_VERTICES 6

class ForwardRenderer2D {

  public:
    ForwardRenderer2D(const glm::ivec2& _bufferSize);

    void Init();

    void Submit(Renderable2D* _entity);
    void Begin();
    void Present();
    void End();

    void DrawString(const std::string& _text, float _x, float _y,
        const Font& _font = *Resources::GetFont(),
        unsigned int _color = 0xffffffff);

    void DrawLine(float _x0, float _y0, float _x1, float _y1,
        unsigned int _color = 0xffffffff, float _thickness = 0.02);

    void DrawLine(const glm::vec2& _start, const glm::vec2& _end,
        unsigned int _color = 0xffffffff, float _thickness = 0.02);

    void DrawRect(float _x, float _y, float _width, float _height,
        unsigned int _color = 0xffffffff, float _thickness = 0.02);

    void DrawRect(const glm::vec2& _location, const glm::vec2& _size,
        unsigned int _color = 0xffffffff, float _thickness = 0.02);

    void DrawRect(const Rect& _rect, unsigned int _color = 0xffffffff,
        float _thickness = 0.02);

    void DrawRect(const Rectangle& _rect, unsigned int _color = 0xffffffff,
        float _thickness = 0.02);


    void FillRect(float _x, float _y, float _width, float _height,
        unsigned int _color = 0xffffffff);

    void FillRect(const glm::vec2& _location, const glm::vec2& _size,
        unsigned int _color = 0xffffffff);

    void FillRect(const Rect& _rect, unsigned int _color = 0xffffffff);

    void FillRect(const Rectangle& _rect, unsigned int _color = 0xffffffff);

    void SetScreenSize(const glm::ivec2& _bufferSize);

    void SetCamera(Camera* _camera);
  private:

    void SubmitTexture(Texture2D* _texture);
    void BindTexture(const std::string& _att, Texture2D* _tex);
    // void BindTextures(const std::string& _att, std::vector<Texture2D*> _tex);

    Texture2D* m_texture;               ///< Only one texture at a time.
    MatrixStack* m_matrixStack;         ///< Rendering matrix stack.
    Shader* m_textureShader;            ///< Shader program for rendering textures.
    Shader* m_textShader;               ///< Shader program fro rendering text.
    VertexBuffer* m_vertexBuffer;             ///< Vertex Array Buffer for rendering.
    VertexArray* m_vertexArray;
    IndexBuffer* m_indexBuffer;
    VertexData m_vertexData[MAX_VERTICES];           ///< Buffer for storing vertex buffer.
    size_t m_indexSize;                 ///< Number of indices that should be rendered.
    glm::ivec2 m_bufferSize;            ///< The size of the rendering buffer.
    Camera* m_camera;                   ///< The scenes camera.

    /// Trying to fix this. Not using the abstracted GL containers
    GLuint vbo, vao, ebo;
    
    
    glm::mat3 t;  
};

#endif