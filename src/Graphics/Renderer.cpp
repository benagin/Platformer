#include <GL/glew.h>

#include "Renderer.hpp"
#include "Application/Resources.hpp"

Renderer::
Renderer(const glm::ivec2& _bufferSize) {
  m_textureShader = nullptr;
  m_textShader = nullptr;
  m_vertexArray = 0;
  m_indexBuffer = 0;
  m_vertexData = nullptr;
  m_indexSize = 0;
  SetScreenSize(_bufferSize);
}

void 
Renderer::
Init() {
  m_matrixStack = new MatrixStack;
  m_matrixStack->pushMatrix();
  m_textureShader = Resources::Get()->GetShader("sprite");
  m_textureShader->AddAttribute("position");
  m_textureShader->AddAttribute("uv");
  m_textureShader->AddAttribute("tid");
  m_textureShader->AddAttribute("color");

  m_textureShader->AddUniform("perspective");
  m_textureShader->AddUniform("transform");

  m_textShader = Resources::Get()->GetShader("text");
  m_vertexData = new VertexData[MAX_TEXTURE_SIZE];
  m_vertexHead = m_vertexData;
  glGenBuffers(1, &m_indexBuffer);
  glGenBuffers(1, &m_vertexArray);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_indexBuffer);

  GLuint* indices = new GLuint[MAX_INDICE_SIZE];
  GLuint offset = 0;
  for(unsigned i = 0; i < MAX_INDICE_SIZE;i += 6) {
    indices[i] = offset + 0;
    indices[i + 1] = offset + 1;
    indices[i + 2] = offset + 2;

    indices[i + 3] = offset + 3;
    indices[i + 4] = offset + 4;
    indices[i + 5] = offset + 5;
    offset += 4;
  }
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, 
    MAX_INDICE_SIZE * sizeof(GLuint),
    indices, GL_STATIC_DRAW);

  

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

  // setting up the attributes of the vertex data.
  glBindBuffer(GL_ARRAY_BUFFER, m_vertexArray);

  // Location Attribute Offset
  offset = 0;
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, offset, 0);
  offset += sizeof(float) * 3;
  
  glEnableVertexAttribArray(1);
  glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, offset, 0);
  offset += sizeof(float) * 2;
  

  glEnableVertexAttribArray(2);
  glVertexAttribPointer(2, 1, GL_FLOAT, GL_FALSE, offset, 0);
  offset += sizeof(float);

  glEnableVertexAttribArray(3);
  glVertexAttribPointer(3, 1, GL_UNSIGNED_INT, GL_FALSE, offset, 0);

  glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void 
Renderer::
Submit(Renderable* _renderable) {
  const auto& bbox = _renderable->GetBoundingBox();

  const auto& min = bbox.GetLowerBounds();
  const auto& max = bbox.GetUpperBounds();
  
  Texture2d* texture = _renderable->Texture();
  const std::vector<glm::vec2>& uvs = _renderable->GetUVs();

  float slot = 0.0f;
  if(texture)
    slot = SubmitTexture(texture);

  // set up vertex buffer
  glm::vec4 vertex = m_matrixStack->topMatrix() * glm::vec4(min, 0.0);
  m_vertexData->m_vertex = glm::vec3(vertex.x, vertex.y, vertex.z);
  m_vertexData->m_uv = uvs[0];
  m_vertexData->m_tid = slot;
  m_vertexData->m_color = 0xffffffff;
  m_vertexData++;
  
  vertex = m_matrixStack->topMatrix() * glm::vec4(max.x, min.y, 0.0, 0.0);
  m_vertexData->m_vertex = glm::vec3(vertex.x, vertex.y, vertex.z);
  m_vertexData->m_uv = uvs[1];
  m_vertexData->m_tid = slot;
  m_vertexData->m_color = 0xffffffff;
  m_vertexData++;

  vertex = m_matrixStack->topMatrix() * glm::vec4(max, 0.0);
  m_vertexData->m_vertex = glm::vec3(vertex.x, vertex.y, vertex.z);
  m_vertexData->m_uv = uvs[2];
  m_vertexData->m_tid = slot;
  m_vertexData->m_color = 0xffffffff;
  m_vertexData++;

  vertex = m_matrixStack->topMatrix() * glm::vec4(min.x, max.y, 0.0, 0.0);
  m_vertexData->m_vertex = glm::vec3(vertex.x, vertex.y, vertex.z);
  m_vertexData->m_uv = uvs[3];
  m_vertexData->m_tid = slot;
  m_vertexData->m_color = 0xffffffff;
  m_vertexData++;

  m_indexSize += 6; 
}

void 
Renderer::
Present() {
  //glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_indexBuffer);
  glBindBuffer(GL_ARRAY_BUFFER, m_vertexArray);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_indexBuffer);
  // Draw
  glDrawElements(GL_TRIANGLES, m_indexSize, GL_UNSIGNED_INT, (void*)0);

  // reinitialize the the index buffer
  m_vertexData = m_vertexHead;
  m_indexSize = 0;
  
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
  glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void 
Renderer::
DrawString(const std::string& _text, float _x, float _y, const Font& _font, unsigned int _color) {

}

void 
Renderer::
DrawLine(float _x0, float _y0, float _x1, float _y1, unsigned int _color, float _thickness) {

}

void 
Renderer::
DrawLine(const glm::vec2& _start, const glm::vec2& _end, unsigned int _color, float _thickness) {

}

void 
Renderer::
DrawRect(float _x, float _y, float _width, float _height, unsigned int _color, float _thickness) {

}

void 
Renderer::
DrawRect(const glm::vec2& _location, const glm::vec2& _size, unsigned int _color, float _thickness) {

}
void
Renderer::
DrawRect(const Rect& _rect, unsigned int _color, float _thickness) {

}

void 
Renderer::
DrawRect(const Rectangle& _rect, unsigned int _color, float _thickness) {

}


void 
Renderer::
FillRect(float _x, float _y, float _width, float _height, unsigned int _color) {

}
void 
Renderer::
FillRect(const glm::vec2& _location, const glm::vec2& _size, unsigned int _color) {

}

void 
Renderer::
FillRect(const Rect& _rect, unsigned int _color) {

}
void 
Renderer::
FillRect(const Rectangle& _rect, unsigned int _color) {

}

void
Renderer::
SetScreenSize(const glm::ivec2& _bufferSize) {
  m_bufferSize = _bufferSize;
  glViewport(0, 0 , m_bufferSize.x, m_bufferSize.y);
}

float
Renderer::
SubmitTexture(Texture2d* _texture) {
  float result = 0.0f; 
  bool found = false;
  for(size_t i = 0; i < m_textures.size(); ++i) {
    if(m_textures[i] == _texture) {
      result = (float) (i + 1);
      found = true;
    }
  }

  if(!found) {
    if(m_textures.size() <= MAX_TEXTURE_SIZE) {
      // present the textures
    }
    m_textures.push_back(_texture);
    result = (float) m_textures.size();
  }
  return result;
}