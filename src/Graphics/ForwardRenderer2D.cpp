#include "ForwardRenderer2D.hpp"
#include <iostream>
using namespace std;


ForwardRenderer2D::
ForwardRenderer2D(const glm::ivec2& _bufferSize) {
  m_textureShader = nullptr;
  m_textShader = nullptr;
  m_vertexBuffer = nullptr;
  m_vertexData = nullptr;
  SetScreenSize(_bufferSize);
}


void
ForwardRenderer2D::
Init() {
  cout << "Initializing Renderer" << endl;

  cout << "Initializing Shader:\n\tAttributes\n\tUniforms\n";

  // create a new matrix stack
  m_matrixStack = new MatrixStack;
  
  // pushing an identity matrix onto stack
  m_matrixStack->pushMatrix();

  // getting the sprite shader from resouces
  m_textureShader = Resources::Get()->GetShader("sprite");

  m_textureShader->Bind();
  // Setting attributes and unifomrs
  m_textureShader->AddAttribute("position");
  m_textureShader->AddAttribute("uv");
  m_textureShader->AddAttribute("tid");
  m_textureShader->AddAttribute("color");

  m_textureShader->AddUniform("projection");
  m_textureShader->AddUniform("textures");

  m_textureShader->Unbind();

  // getting the text shader, The sprite shader might be used to render this.
  m_textShader = Resources::Get()->GetShader("text");
  cout << "Shader Complete\n";

  cout << "Generating Buffers" << endl;

  m_vertexBuffer = new VertexBuffer(MAX_VERTICES, Usage::DynamicDraw);
  m_vertexBuffer->Resize(MAX_VERTICES); // I know this is redundant

  // getting the data from the buffer 
  cout << "Setting up Vertex Attributes" << endl;
  m_vertexArray = new VertexArray;

  m_vertexArray->Bind();
  m_vertexArray->AddBuffer(m_vertexBuffer);
  
  GLuint offset = 0;
  m_vertexBuffer->Bind(); 

  glEnableVertexAttribArray(0);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, offset, 0);
  glCheckError();

  offset += sizeof(float) * 3;

  glEnableVertexAttribArray(1);
  glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, offset, 0);
  glCheckError();
  
  offset += sizeof(float) * 2;

  glEnableVertexAttribArray(2);
  glVertexAttribPointer(2, 1, GL_FLOAT, GL_FALSE, offset, 0);
  glCheckError();

  offset += sizeof(float);

  glEnableVertexAttribArray(3);
  glCheckError();
  glVertexAttribPointer(3, 1, GL_UNSIGNED_INT, GL_FALSE, offset, 0);
  cout << "Finished Vertex Attributes" << endl;

  m_vertexBuffer->Unbind();
  m_vertexArray->Unbind();
  m_textureShader->Unbind();
  
  cout << "Initialized Renderer" << endl;
}


void
ForwardRenderer2D::
Submit(Renderable2D* _renderable) {
  const auto& bbox = _renderable->GetBoundingBox();

  const auto& min = bbox.GetLowerBounds();
  const auto& max = bbox.GetUpperBounds();

  Texture2D* texture = _renderable->Texture();
  const std::vector<glm::vec2>& uvs = _renderable->GetUVs();
  
  SubmitTexture(texture);

  glm::vec4 vertex = m_matrixStack->topMatrix() * glm::vec4(min, 0.0);
  m_vertexData->m_vertex = glm::vec3(vertex.x, vertex.y, vertex.z);
  m_vertexData->m_uv = uvs[0];
  m_vertexData->m_tid = 0.5f;
  m_vertexData->m_color = 0xffffffff;
  m_vertexData++;

  vertex = m_matrixStack->topMatrix() * glm::vec4(max.x, min.y, 0.0, 0.0);
  m_vertexData->m_vertex = glm::vec3(vertex.x, vertex.y, vertex.z);
  m_vertexData->m_uv = uvs[1];
  m_vertexData->m_tid = 0.5f;
  m_vertexData->m_color = 0xffffffff;
  m_vertexData++;

  vertex = m_matrixStack->topMatrix() * glm::vec4(max, 0.0);
  m_vertexData->m_vertex = glm::vec3(vertex.x, vertex.y, vertex.z);
  m_vertexData->m_uv = uvs[2];
  m_vertexData->m_tid = 0.5f;
  m_vertexData->m_color = 0xffffffff;
  m_vertexData++;

  vertex = m_matrixStack->topMatrix() * glm::vec4(min.x, max.y, 0.0, 0.0);
  m_vertexData->m_vertex = glm::vec3(vertex.x, vertex.y, vertex.z);
  m_vertexData->m_uv = uvs[3];
  m_vertexData->m_tid = 0.5f;
  m_vertexData->m_color = 0xffffffff;
  m_vertexData++;

  Present();
}


void
ForwardRenderer2D::
Begin() {
  m_vertexArray->Bind();
  m_vertexData = (VertexData*) m_vertexArray->GetBuffer()->Pointer();
  glCheckError();
}


void
ForwardRenderer2D::
Present() {
  m_textureShader->Bind();
  m_textureShader->SetMatrix4("projection", m_camera->GetProjection());

  auto unit = m_textureShader->GetUniform("textures");
  m_texture->SetUnit(unit);
  m_texture->Bind();
  m_vertexArray->Bind();

  glDrawArrays(GL_TRIANGLES, 0, 6);
  glCheckError();

  m_vertexArray->Unbind();

  m_texture->Unbind();

  m_textureShader->Unbind();
}


void
ForwardRenderer2D::
End() {
  m_vertexArray->GetBuffer()->Release();
  m_vertexArray->Unbind();
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