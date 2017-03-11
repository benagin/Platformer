#ifndef ENTITY_HPP_
#define ENTITY_HPP_
#include "Graphics/Renderable2D.hpp"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Utilities/GLDebug.hpp"

// This might not be necissary.
enum EntityType {
  Basic,
  Static,
  Dynamic,
  Player
};

class Entity : public Renderable2D {

  public:
    Entity(Texture2D* _tex, const glm::vec3& _loc,
      const glm::vec2& _size, float _rotation = 0.0f, EntityType _type = Basic);

    EntityType GetType() const { return m_type; }
  private:
    EntityType m_type;
};

#endif // ENTITY_HPP_
