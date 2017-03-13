#include <GL/glew.h>

#include "Renderer2D.hpp"
#include "Application/Resources.hpp"
#include "Utilities/GLDebug.hpp"

#include <iostream>
using namespace std;


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

  cout << "Initializing Renderer" << endl;

  cout << "Initializing Shader:\nAttributes\nUniforms\n";

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

  // Stored the indices for textures
  cout << "Generating Buffers" << endl;

  VertexBuffer* buffer = new VertexBuffer(MAX_BUFFER_SIZE, Usage::DynamicDraw);
  buffer->Resize(MAX_BUFFER_SIZE); // I know this is redundant 

  m_vertexArray = new VertexArray;

  // getting the data from the buffer 
  cout << "Setting up Vertex Attributes" << endl;
  
  GLuint offset = 0;
  m_vertexArray->Bind();
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, offset, 0);
  glCheckError();

  offset += sizeof(float) * 3;

  glEnableVertexAttribArray(1);
  glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, offset, (void*)(3 * sizeof(float)));
  glCheckError();
  
  offset += sizeof(float) * 2;

  glEnableVertexAttribArray(2);
  glVertexAttribPointer(2, 1, GL_FLOAT, GL_FALSE, offset, (void*)(5 * sizeof(float)));
  glCheckError();

  offset += sizeof(float);

  glEnableVertexAttribArray(3);
  glCheckError();
  glVertexAttribPointer(3, 1, GL_UNSIGNED_INT, GL_FALSE, offset, (void*)(6 * sizeof(float)));
  cout << "Finished Vertex Attributes" << endl;

  m_vertexArray->AddBuffer(buffer);

  // setting up the indices.
  cout << "Initiallizing Indicies" << endl;
  
  GLuint* indices = new GLuint[MAX_INDICE_SIZE];
  offset = 0;
  for(unsigned i = 0; i < MAX_INDICE_SIZE;i += 6) {
    indices[i] = offset + 0;
    indices[i + 1] = offset + 1;
    indices[i + 2] = offset + 2;

    indices[i + 3] = offset + 3;
    indices[i + 4] = offset + 4;
    indices[i + 5] = offset + 5;
    offset += 4;
  }

  m_indexBuffer = new IndexBuffer(indices, MAX_INDICE_SIZE);

  m_vertexArray->Unbind();
  m_textureShader->Unbind();
  
  cout << "Initialized Renderer" << endl;
}


void
Renderer::
Submit(Renderable2D* _renderable) {
  const auto& bbox = _renderable->GetBoundingBox();

  const auto& min = bbox.GetLowerBounds();
  const auto& max = bbox.GetUpperBounds();

  Texture2D* texture = _renderable->Texture();
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
Begin() {
  m_vertexArray->Bind();
  glCheckError();
  m_vertexData = (VertexData*) m_vertexArray->GetBuffer()->Pointer();
  glCheckError();
}


void
Renderer::
Present() {
  // set shader values
  m_textureShader->Bind();
  m_textureShader->SetMatrix4("projection", m_camera->GetProjection());

  auto unit = m_textureShader->GetUniform("textures");
  for(auto i : m_textures) {
    i->SetUnit(unit);
    i->Bind();
    ++unit;
  }

  m_vertexArray->Bind();
  m_indexBuffer->Bind();


  // Draw
  m_vertexArray->Draw(m_indexSize);
  glCheckError();

  m_indexSize = 0;

  m_indexBuffer->Unbind();
  m_vertexArray->Unbind();

  for(auto i : m_textures) {
    i->Unbind();
  }
  m_textures.clear();
  
  m_textureShader->Unbind();
}

void
Renderer::
End() {
  m_vertexArray->GetBuffer()->Release();
  m_vertexArray->Unbind();
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
SubmitTexture(Texture2D* _texture) {
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
      End();
      Present();
      Begin();
    }
    m_textures.push_back(_texture);
    result = (float) m_textures.size();
  }
  return result;
}


void
Renderer::
SetCamera(Camera* _camera) {
  m_camera = _camera;
}