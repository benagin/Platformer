///////////////////////////////////////////////////////////////////////////////
/// @name Renderable
/// @group NA
/// @Author Andrew Bregger 19/02/2017
///
/// @brief A base class for any entity that can be rendered.
///
/// @note: this can be implemented by either storing the id of
///				 texture or a reference to the texture itself.
///
/// 				For now, I'm storing the texture
///////////////////////////////////////////////////////////////////////////////
#ifndef RENDERABLE_HPP_
#define RENDERABLE_HPP_

#include <GL/glew.h>

#include <glm/glm.hpp>
#include "Texture2d.hpp"
#include "Shader.hpp"

class Renderable {
public:
	Renderable(Texture2d& _tex, const glm::vec3& _loc, const glm::vec2& _size, float _rotation = 0.0f);

	virtual ~Renderable() = default;

	virtual void Draw(Shader& _shader) = 0;

	static void Init();

	void SetLocation(const glm::vec3& _loc);
	void SetRotation(float _rot);


protected:
	glm::vec3 m_location;
	glm::vec2 m_size;

	float m_rotation;

	Texture2d& m_texture;
	static GLuint VAO;
};


#endif
