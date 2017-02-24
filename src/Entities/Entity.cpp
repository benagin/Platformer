#include "Entity.hpp"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "utils/GLDebug.hpp"

/// Gets changed to sprite instead of Texture
Entity::
Entity(Texture2d& _tex, const glm::vec3& _loc,
		const glm::vec2& _size, float _rotation, Entity_Type _type):
		Renderable(_tex, _loc, _size, _rotation), m_type(_type) {}


void
Entity::
Draw(Shader& _shader) {
	_shader.Bind();
	glm::mat4 model;
	model = glm::translate(model, this->m_location);
	model = glm::rotate(model, this->m_rotation, glm::vec3(0,0,1));
	model = glm::scale(model, glm::vec3(m_size, 1.0));
	glUniformMatrix4fv(_shader.GetUniform("model"), 1,
      GL_FALSE, glm::value_ptr(model));
  glUniform3f(_shader.GetUniform("spriteColor"), 
  	1.f, 1.f, 1.f);
  
  this->m_texture.Bind();

  glActiveTexture(GL_TEXTURE0);
  glBindVertexArray(VAO);
  glDrawArrays(GL_TRIANGLE_STRIP, 0, 6);
  glBindVertexArray(0);

  _shader.Unbind();
  glCheckError();
}