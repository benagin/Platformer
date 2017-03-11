#ifndef GUI_ELEMENT_HPP_
#define GUI_ELEMENT_HPP_

#include "Graphics/Renderable2D.hpp"

class GUIElement : public Renderable2D {

  public:

    GUIElement(Texture2D* _tex, const glm::vec3& _loc, const glm::vec2& _size,
        float _rotation = 0.0f) : Renderable2D(_tex, _loc, _size, _rotation) {}

    virtual ~GUIElement() = default;

    void Draw(const Shader& _shader) const {}


  protected:

};

#endif
