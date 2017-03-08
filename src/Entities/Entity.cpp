#include "Entity.hpp"


Entity::
Entity(Texture2d* _tex, const glm::vec3& _loc,
		const glm::vec2& _size, float _rotation, EntityType _type):
		Renderable(_tex, _loc, _size, _rotation), m_type(_type) {}
