#include "ForwardRenderer2D.hpp"
#include <glm/gtc/matrix_transform.hpp>

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
  glCheckError();
  // Setting attributes and unifomrs
  m_textureShader->AddAttribute("vertex");

  m_textureShader->AddUniform("projection");
  m_textureShader->AddUniform("modelview");
  m_textureShader->AddUniform("textures");
  m_textureShader->AddUniform("color");
  
  auto perspective = glm::ortho(0.0f, (float) m_bufferSize.x, (float) m_bufferSize.y, 0.0f, -1.0f, 1.0f);
  m_textureShader->SetMatrix4("projection", perspective);
  m_textureShader->SetVector3f("color", 1.0f, 1.0f, 1.0f);

  m_textureShader->Unbind();

  // getting the text shader, The sprite shader might be used to render this.
  m_textShader = Resources::Get()->GetShader("text");


  /*
  GLfloat vertices[] = {
        // Positions            // Texture Coords
        1.f, 1.f, 1.0f, 1.0f,   // Top Right
        1.f, 0.f, 1.0f, 0.0f,   // Bottom Right
        0.f, 0.f, 0.0f, 0.0f,   // Bottom Left
        0.f, 1.f, 0.0f, 1.0f,   // Top Left 
  }; 
  */

  GLfloat vertices[] = {
    0.0f, 1.0f, 0.0f, 1.0f,
    1.0f, 0.0f, 1.0f, 0.0f,
    0.0f, 0.0f, 0.0f, 0.0f, 

    0.0f, 1.0f, 0.0f, 1.0f,
    1.0f, 1.0f, 1.0f, 1.0f,
    1.0f, 0.0f, 1.0f, 0.0
  };
 /* 
  GLuint indices[] = {
    0, 1, 3,
    1, 2, 3
  };
  */

  glGenVertexArrays(1, &vao);
  glGenBuffers(1, &vbo);
//   glGenBuffers(1, &ebo);

  glBindVertexArray(vao);

  glBindBuffer(GL_ARRAY_BUFFER, vbo);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

//   glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
//   glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

  glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (GLvoid*)0);
  glEnableVertexAttribArray(0);
  glCheckError();

  glBindVertexArray(0); // Unbind VAO 
  
  cout << "Finished Renderer" << endl;
}


void
ForwardRenderer2D::
Submit(Renderable2D* _renderable) {
  auto texture = _renderable->Texture();

  m_textureShader->Bind();
  SubmitTexture(texture);
  BindTexture("textures", m_texture);

  m_matrixStack->pushMatrix();
  m_matrixStack->translate(_renderable->GetLocation());
  m_matrixStack->rotate(_renderable->GetRotation(), glm::vec3(0,0,1));
  m_matrixStack->scale(_renderable->GetSize());

  m_textureShader->SetMatrix4("modelview", m_matrixStack->topMatrix());
  m_textureShader->Unbind();

  m_matrixStack->popMatrix();

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
  glCheckError(); 

  // m_texture->Bind();

  // m_vertexArray->Bind();
  // m_indexBuffer->Bind();

  // m_vertexArray->Draw(6);
  glBindVertexArray(vao);
//   glDrawElements(GL_TRIANGLE_STRIP, 6, GL_UNSIGNED_INT, 0);
  glDrawArrays(GL_TRIANGLE_STRIP, 0, 6);
  glCheckError();
  glBindVertexArray(0);

  // m_indexBuffer->Unbind();
  // m_vertexArray->Unbind();
  // m_texture->Unbind();

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