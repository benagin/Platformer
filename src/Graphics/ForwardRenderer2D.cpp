#include "ForwardRenderer2D.hpp"
#include <iostream>
using namespace std;


ForwardRenderer2D::
ForwardRenderer2D(const glm::ivec2& _bufferSize) {
  m_textureShader = nullptr;
  m_textShader = nullptr;
  m_vertexBuffer = nullptr;
  SetScreenSize(_bufferSize);
}


void
ForwardRenderer2D::
Init() {
  cout << "Initializing Renderer" << endl;


  // create a new matrix stack
  m_matrixStack = new MatrixStack;
  
  // pushing an identity matrix onto stack
  m_matrixStack->pushMatrix();

  // getting the sprite shader from resouces
  m_textureShader = Resources::Get()->GetShader("forward");

  m_textureShader->Bind();
  // Setting attributes and unifomrs
  m_textureShader->AddAttribute("position");
  m_textureShader->AddAttribute("uv");

  m_textureShader->AddUniform("projection");
  m_textureShader->AddUniform("modelview");
  // m_textureShader->AddUniform("textureMatrix");
  m_textureShader->AddUniform("textures");

  m_textureShader->Unbind();

  // getting the text shader, The sprite shader might be used to render this.
  m_textShader = Resources::Get()->GetShader("text");

  GLfloat vertices[] = {
        // Positions          // Colors           // Texture Coords
         0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f, // Top Right
         0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f, // Bottom Right
        -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f, // Bottom Left
        -0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f  // Top Left 
  }; 

  GLuint indices[] = {
    0, 1, 3,
    1, 2, 3
  };
  m_vertexArray = new VertexArray;
  m_vertexBuffer = new VertexBuffer(MAX_VERTICES, Usage::StaticDraw);
  m_vertexArray->Bind();

  m_vertexBuffer->SetData(vertices, MAX_VERTICES);
  m_vertexBuffer->Bind();
  m_indexBuffer = new IndexBuffer(indices, 6);

  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)0);
  glEnableVertexAttribArray(0);
  // Color attribute
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
  glEnableVertexAttribArray(1);
  // TexCoord attribute
  glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(6 * sizeof(GLfloat)));
  glEnableVertexAttribArray(2);

  m_vertexArray->Unbind();
  glCheckError();

  m_textureShader->Bind();
  t[0][0] = 1;  
  // m_textureShader->SetMatrix3("textureMatrix", t);
  glCheckError();

  m_vertexBuffer->Unbind();
  m_vertexArray->Unbind();
  m_textureShader->Unbind();

  cout << "Finished Renderer" << endl;
}


void
ForwardRenderer2D::
Submit(Renderable2D* _renderable) {
  auto texture = _renderable->Texture();

  m_textureShader->Bind();
  SubmitTexture(texture);
  m_textureShader->SetMatrix4("modelview", _renderable->GetTransform());
  m_textureShader->Unbind();
  
  Present();
}


void
ForwardRenderer2D::
Begin() {
}


void
ForwardRenderer2D::
Present() {
  m_textureShader->Bind();
  glCheckError(); 
  m_textureShader->SetMatrix4("projection", m_camera->GetProjection());
  glCheckError(); 

  // m_texture->Bind();
  BindTexture("textures", m_texture);

  m_vertexArray->Bind();
  m_indexBuffer->Bind();

  m_vertexArray->Draw(6);
  // glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

  m_indexBuffer->Unbind();
  m_vertexArray->Unbind();
  m_texture->Unbind();

  m_textureShader->Unbind();
  glCheckError();
}


void
ForwardRenderer2D::
End() {
}


void
ForwardRenderer2D::
DrawString(const std::string& _text, float _x, float _y,
    const Font& _font,
    unsigned int _color) {

}


void
ForwardRenderer2D::
DrawLine(float _x0, float _y0, float _x1, float _y1,
    unsigned int _color, float _thickness) {

}


void
ForwardRenderer2D::
DrawLine(const glm::vec2& _start, const glm::vec2& _end,
    unsigned int _color, float _thickness) {

}


void
ForwardRenderer2D::
DrawRect(float _x, float _y, float _width, float _height,
    unsigned int _color, float _thickness) {

}


void
ForwardRenderer2D::
DrawRect(const glm::vec2& _location, const glm::vec2& _size,
    unsigned int _color, float _thickness) {

}


void
ForwardRenderer2D::
DrawRect(const Rect& _rect, unsigned int _color,
    float _thickness) {

}


void
ForwardRenderer2D::
DrawRect(const Rectangle& _rect, unsigned int _color,
    float _thickness) {

}


void
ForwardRenderer2D::
FillRect(float _x, float _y, float _width, float _height,
    unsigned int _color) {

}


void
ForwardRenderer2D::
FillRect(const glm::vec2& _location, const glm::vec2& _size,
    unsigned int _color) {

}


void
ForwardRenderer2D::
FillRect(const Rect& _rect, unsigned int _color) {

}


void
ForwardRenderer2D::
FillRect(const Rectangle& _rect, unsigned int _color) {

}

void
ForwardRenderer2D::
SetScreenSize(const glm::ivec2& _bufferSize) {
  m_bufferSize = _bufferSize;
}

void
ForwardRenderer2D::
SetCamera(Camera* _camera) {
  m_camera = _camera;
}


void
ForwardRenderer2D::
SubmitTexture(Texture2D* _texture) {
  m_texture = _texture;
}
void
ForwardRenderer2D::
BindTexture(const std::string& _att, Texture2D* _tex) {
  _tex->SetUnit(0);
  _tex->Bind();
  m_textureShader->SetInteger("textures", _tex->GetUnit());
}