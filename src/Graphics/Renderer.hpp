// Basic structure is taken from Sparky Game Engine.
// https://github.com/TheCherno/Sparky
#ifndef RENDERER_HPP_
#define RENDERER_HPP_
#include <glm/glm.hpp>
#include <string>
#include <vector>


#include "Application/Resources.hpp"
#include "Font.hpp"
#include "Utils/MatrixStack.h"
#include "Renderable.hpp"
#include "Shader.hpp"

#define MAX_TEXTURE_SIZE 60000
#define MAX_INDICE_SIZE MAX_TEXTURE_SIZE * 6

class Renderer {
  public:
    Renderer(const glm::ivec2& _bufferSize);
    void Init();

    void Submit(Renderable* _entity);
    void Present();

    void DrawString(const std::string& _text, float _x, float _y, const Font& _font = *Resources::GetFont(), unsigned int _color = 0xffffffff);
    void DrawLine(float _x0, float _y0, float _x1, float _y1, unsigned int _color = 0xffffffff, float _thickness = 0.02);
    void DrawLine(const glm::vec2& _start, const glm::vec2& _end, unsigned int _color = 0xffffffff, float _thickness = 0.02);
    
    void DrawRect(float _x, float _y, float _width, float _height, unsigned int _color = 0xffffffff, float _thickness = 0.02);
    void DrawRect(const glm::vec2& _location, const glm::vec2& _size, unsigned int _color = 0xffffffff, float _thickness = 0.02);
    void DrawRect(const Rect& _rect, unsigned int _color = 0xffffffff, float _thickness = 0.02);
    void DrawRect(const Rectangle& _rect, unsigned int _color = 0xffffffff, float _thickness = 0.02);


    void FillRect(float _x, float _y, float _width, float _height, unsigned int _color = 0xffffffff);
    void FillRect(const glm::vec2& _location, const glm::vec2& _size, unsigned int _color = 0xffffffff);
    void FillRect(const Rect& _rect, unsigned int _color = 0xffffffff);
    void FillRect(const Rectangle& _rect, unsigned int _color = 0xffffffff);

    void SetScreenSize(const glm::ivec2& _bufferSize);

  private:
    float SubmitTexture(Texture2d* _texture);
    //std::vector<Entity*> m_entities;
    std::vector<Texture2d*> m_textures;
    MatrixStack* m_matrixStack;
    Shader* m_textureShader;
    Shader* m_textShader;
    GLuint m_vertexArray;
    GLuint m_indexBuffer;
    VertexData* m_vertexData;
    VertexData* m_vertexHead;
    size_t m_indexSize;
    glm::ivec2 m_bufferSize;
    // Camera m_camera;
};


#endif