#include "Entity.hpp"

Entity::
Entity(Texture2D* _tex, const glm::vec3& _loc,
		const glm::vec2& _size, float _rotation, EntityType _type):
		Renderable2D(_tex, _loc, _size, _rotation), m_type(_type) {}