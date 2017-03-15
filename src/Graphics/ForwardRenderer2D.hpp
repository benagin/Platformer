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

/// @brief A renderer for 2D objects
class ForwardRenderer2D {

  public:
    ///////////////////////////////////////////////////////////////////////////
    /// @name Constructors
    /// @{

    /// @brief Renderer Constructor
    /// @param _bufferSize The size of the renderering screen.
    ForwardRenderer2D(const glm::ivec2& _bufferSize);

    /// @}
    /// @name Initialization
    /// @{

    void Init();
    
    /// @}
    /// @name Rendering Textures
    /// @{

    /// @brief Renderer Constructor
    /// @param _renderable The renderable object that is begin rendered
    void Submit(Renderable2D* _renderable);

    /// @brief Doesnt do anything
    void Begin();

    /// @brief Renders the current texture to the screen
    void Present();
    
    /// @brief Doesnt do anything
    void End();

    /// @}
    /// @name 2D Primative rendering
    /// @{
    
    /// @brief Renderer a string to the screen
    /// @param _text The string being rendered
    /// @param _x The x coordinate to start rendering.
    /// @param _y The y corrdinate to start rendering.
    /// @param _font The font to be used when rendering the text.
    /// @param _color The color of the text.
    void DrawString(const std::string& _text, float _x, float _y,
        const Font& _font = *Resources::GetFont(),
        unsigned int _color = 0xffffffff);

    /// @brief Render a line to the screen
    /// @param _x0 The starting x coordinate.
    /// @param _y0 The starting y coordinate.
    /// @param _x1 The ending x coordinate.
    /// @param _y1 The ending y coordinate.
    /// @param _color The color of the line.
    /// @param _thickness The thickness of the line.
    void DrawLine(float _x0, float _y0, float _x1, float _y1,
        unsigned int _color = 0xffffffff, float _thickness = 0.02);

    /// @brief Render a line to the screen
    /// @param _start A vector to the starting coordinate.
    /// @param _end A vector to the ending coordinate.
    /// @param _color The color of the line.
    /// @param _thickness The thickness of the line.
    void DrawLine(const glm::vec2& _start, const glm::vec2& _end,
        unsigned int _color = 0xffffffff, float _thickness = 0.02);

    /// @brief Render a rectangle to the screen.
    /// @param _x The x coordinate of the lower left corner.
    /// @param _y The y corrdinate of the lower left corner.
    /// @param _width The width of the rectangle.
    /// @param _height The height of the rectangle.
    /// @param _color The color of the line.
    /// @param _thickness The thickness of the line.
    void DrawRect(float _x, float _y, float _width, float _height,
        unsigned int _color = 0xffffffff, float _thickness = 0.02);

    /// @brief Render a rectangle to the screen.
    /// @param _location The coordinates of the lower left corner.
    /// @param _size The size of the rectangle: x = width, y = height.
    /// @param _color The color of the line.
    /// @param _thickness The thickness of the line.
    void DrawRect(const glm::vec2& _location, const glm::vec2& _size,
        unsigned int _color = 0xffffffff, float _thickness = 0.02);

    /// @brief Render a rectangle to the screen.
    /// @param _rect A rectangle to be drawn
    /// @param _color The color of the line.
    /// @param _thickness The thickness of the line.
    void DrawRect(const Rect& _rect, unsigned int _color = 0xffffffff,
        float _thickness = 0.02);

    /// @brief Render a rectangle to the screen.
    /// @param _rect A rectangle to be drawn.
    /// @param _color The color of the line.
    /// @param _thickness The thickness of the line.
    void DrawRect(const Rectangle& _rect, unsigned int _color = 0xffffffff,
        float _thickness = 0.02);


    /// @brief Render a filled in rectangle
    /// @param _x0 The starting x coordinate.
    /// @param _y0 The starting y coordinate.
    /// @param _x1 The ending x coordinate.
    /// @param _y1 The ending y coordinate.
    /// @param _color Color to be used.
    void FillRect(float _x, float _y, float _width, float _height,
        unsigned int _color = 0xffffffff);

    /// @brief Render a filled in rectangle
    /// @param _location The coordinates of the lower left corner.
    /// @param _size The size of the rectangle: x = width, y = height.
    /// @param _color The color to be used.
    void FillRect(const glm::vec2& _location, const glm::vec2& _size,
        unsigned int _color = 0xffffffff);

    /// @brief Render a filled in rectangle
    /// @param _rect A rectangle to be drawn
    /// @param _color The color of the line.
    /// @param _thickness The thickness of the line.
    /// @param _color The color to be used.
    void FillRect(const Rect& _rect, unsigned int _color = 0xffffffff);

    /// @brief Render a filled in rectangle
    /// @param _rect A rectangle to be drawn.
    /// @param _color The color of the line.
    /// @param _thickness The thickness of the line.
    /// @param _color The color to be used.
    void FillRect(const Rectangle& _rect, unsigned int _color = 0xffffffff);

    /// @{
    /// @name Setters
    /// @{
        
    /// @brief Sets the screen size used by the renderer.
    /// @param _bufferSize Size of the screen.
    void SetScreenSize(const glm::ivec2& _bufferSize);

    /// @brief Sets the camera begin used by the Renderer.
    /// @param _camera A pointer to the Camera.
    void SetCamera(Camera* _camera);
    
    /// @{
  private:
  
    /// @name Helper functions.
    /// @{

    /// @brief Set up the renderer to render the texture.
    /// @param _texture The texture.
    void SubmitTexture(Texture2D* _texture);

    /// @brief Binds the texture to the shader.
    /// @param _att The attribute name of the texture in the shader.
    /// @param _tex The texture being bound.
    void BindTexture(const std::string& _att, Texture2D* _tex);

    /// @{

    Texture2D* m_texture;               ///< Only one texture at a time.
    MatrixStack* m_matrixStack;         ///< Rendering matrix stack.
    Shader* m_textureShader;            ///< Shader program for rendering textures.
    Shader* m_textShader;               ///< Shader program fro rendering text.
    VertexBuffer* m_vertexBuffer;       ///< Vertex Array Buffer for rendering.
    VertexArray* m_vertexArray;         ///< Vertex array for rendering textures
    size_t m_indexSize;                 ///< Number of indices that should be rendered.
    glm::ivec2 m_bufferSize;            ///< The size of the rendering buffer.
    Camera* m_camera;                   ///< The scenes camera.
    
    
    glm::mat3 t;  
};

#endif