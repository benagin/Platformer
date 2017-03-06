#include "Entity.hpp"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "utils/GLDebug.hpp"

Entity::
Entity(Texture2d* _tex, const glm::vec3& _loc,
		const glm::vec2& _size, float _rotation, Entity_Type _type):
		Renderable(_tex, _loc, _size, _rotation), m_type(_type) {}
