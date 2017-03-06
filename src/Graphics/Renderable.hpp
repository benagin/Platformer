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
#include <vector>

#include "Texture2d.hpp"
#include "Shader.hpp"
#include "Utils/Rect.hpp"

struct VertexData {
	glm::vec3 m_vertex;
	glm::vec2 m_uv;
	float m_tid;
	unsigned int m_color;
};

class Renderer;

class Renderable {
public:
	Renderable(Texture2d* _tex, const glm::vec3& _loc, const glm::vec2& _size, float _rotation = 0.0f);

	virtual ~Renderable() = default;

	static void Init();

	void SetLocation(const glm::vec3& _loc);
	void SetRotation(float _rot);
	const std::vector<glm::vec2>& GetUVs() { return m_uvs; }
	void Submit(Renderer* _renderer);
	Texture2d* Texture();
	const Rect& GetBoundingBox() { return m_bbox; }
	static const std::vector<glm::vec2>& DefaultUVs();
protected:
	glm::vec3 m_location;
	glm::vec2 m_size;
	float m_rotation;
	Texture2d* m_texture;
	Rect m_bbox;
	std::vector<glm::vec2> m_uvs;

};


#endif