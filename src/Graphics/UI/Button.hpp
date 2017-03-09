#ifndef BUTTON_HPP_
#define BUTTON_HPP_

#include "GUIElement.hpp"

class Button  : public GUIElement{

  public:

    Button() {}

    Button(Texture2d* _tex, const glm::vec3& _loc, const glm::vec2& _size,
        float _rotation = 0.0f) : GUIElement(_tex, _loc, _size, _rotation) {}

    ~Button() {}
}

#endif
