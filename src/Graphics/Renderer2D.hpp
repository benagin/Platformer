// Basic structure is taken from Sparky Game Engine.
// https://github.com/TheCherno/Sparky
#ifndef RENDERER_HPP_
#define RENDERER_HPP_

#include <glm/glm.hpp>
#include <string>
#include <vector>

#include "Application/Resources.hpp"
#include "Graphics/Camera.hpp"
#include "gl/VertexArray.hpp"
#include "gl/VertexBuffer.hpp"
#include "gl/IndexBuffer.hpp"
#include "Font.hpp"
#include "Utilities/MatrixStack.hpp"
#include "Utilities/Rect.hpp"
#include "Renderable2D.hpp"
#include "Shader.hpp"

#define MAX_TEXTURE_SIZE 60000
#define MAX_INDICE_SIZE MAX_TEXTURE_SIZE * 6
#define MAX_BUFFER_SIZE (MAX_TEXTURE_SIZE * 4 * sizeof(VertexData))

class Renderable;

struct VertexData {
	glm::vec3 m_vertex;
	glm::vec2 m_uv;
	float m_tid;
	unsigned int m_color;
};


class Renderer {

  public:

    Renderer(const glm::ivec2& _bufferSize);

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

    float SubmitTexture(Texture2D* _texture);

    std::vector<Texture2D*> m_textures; ///< List of currently rendered textures.
    MatrixStack* m_matrixStack;         ///< Rendering matrix stack.
    Shader* m_textureShader;            ///< Shader program for rendering textures.
    Shader* m_textShader;               ///< Shader program fro rendering text.
    VertexArray* m_vertexArray;         ///< Vertex Array object for rendering.
    IndexBuffer* m_indexBuffer;         ///< Single buffer for storing indices.
    VertexData* m_vertexData;           ///< Buffer for storing vertex buffer.
    size_t m_indexSize;                 ///< Number of indices that should be rendered.
    glm::ivec2 m_bufferSize;            ///< The size of the rendering buffer.
    Camera* m_camera;                   ///< The scenes camera.
};


#endif
