#ifndef ENTITY_HPP_
#define ENTITY_HPP_
#include "graphics/Renderable2D.hpp"
#include <glm/glm.hpp>

// this might not be necissary.
enum Entity_Type {
	Basic,
	Static,
	Dynamic,
	Player
};


class Entity : public Renderable2D {
  public:
    Entity(Texture2D* _tex, const glm::vec3& _loc,
      const glm::vec2& _size, float _rotation = 0.0f, Entity_Type _type = Basic);
  private:
    Entity_Type m_type;
};

#endif // ENTITY_HPP_
