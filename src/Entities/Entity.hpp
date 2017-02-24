#ifndef ENTITY_HPP_
#define ENTITY_HPP_
#include "graphics/Renderable.hpp"

// this might not be necissary.
enum Entity_Type {
	BASIC,
	STATIC,
	DYNAMIC,
	PLAYER
};


class Entity : public Renderable {
public:
	Entity(Texture2d& _tex, const glm::vec3& _loc,
		const glm::vec2& _size, float _rotation = 0.0f, Entity_Type _type = BASIC);

	virtual ~Entity() = default;

	virtual void Draw(Shader& _shader);
private:
	Entity_Type m_type;
};

#endif // ENTITY_HPP_
