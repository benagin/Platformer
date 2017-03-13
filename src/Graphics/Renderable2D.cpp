#include "Renderable2D.hpp"
#include "Graphics/Renderer2D.hpp"
#include "Utilities/GLDebug.hpp"
#include "Utilities/MatrixStack.hpp"

Renderable2D::
Renderable2D(Texture2D* _tex, const glm::vec3& _loc,
	const glm::vec2& _size, float _rotation): m_location(_loc),
	m_size(_size), m_rotation(_rotation), m_texture(_tex) {
  m_bbox = {m_location.x, m_location.y, m_location.x + m_size.x, m_location.y + m_size.y};
  m_uvs = DefaultUVs();
}


/*
void
Renderable2D::
Init() {
	GLuint spriteVBO;
	GLfloat vertices[] = {
    // Pos      // Tex
    0.0f, 1.0f, 0.0f, 1.0f,
    1.0f, 0.0f, 1.0f, 0.0f,
    0.0f, 0.0f, 0.0f, 0.0f,

    0.0f, 1.0f, 0.0f, 1.0f,
    1.0f, 1.0f, 1.0f, 1.0f,
    1.0f, 0.0f, 1.0f, 0.0f
	};

  glGenVertexArrays(1, &VAO);
  glGenBuffers(1, &spriteVBO);

  glBindBuffer(GL_ARRAY_BUFFER, spriteVBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

  glBindVertexArray(VAO);
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (GLvoid*)0);
  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindVertexArray(0);
  glCheckError();
}
*/

void 
Renderable2D::
SetLocation(const glm::vec3& _loc) {
	m_location = _loc;
}


void 
Renderable2D::
SetRotation(float _rot) {
	m_rotation = _rot;
}

void
Renderable2D::
Submit(Renderer* _renderer) {
  _renderer->Submit(this);
}

const std::vector<glm::vec2>& 
Renderable2D::
DefaultUVs() {
  static std::vector<glm::vec2> uvs;
  if(!uvs.size()) {
    uvs.push_back(glm::vec2(0, 0));
    uvs.push_back(glm::vec2(1, 0));
    uvs.push_back(glm::vec2(1, 1));
    uvs.push_back(glm::vec2(0, 1));
  }
  return uvs;
}

Texture2D*
Renderable2D::
Texture() {
  return m_texture;
}

glm::mat4
Renderable2D::
GetTransform() {
  MatrixStack ms;
  ms.pushMatrix();
  ms.translate(m_location);
  ms.rotate(m_rotation, glm::vec3(0, 1, 0));
  ms.scale(m_size.x, m_size.y, 1);
  return ms.topMatrix();
}