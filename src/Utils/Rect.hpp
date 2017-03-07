#ifndef RECT_HPP_
#define RECT_HPP_

#include <glm/glm.hpp>

struct Rectangle {
  float x, y, h, w;
};

struct Rect {
  float x, y, maxx, maxy;
  glm::vec3 GetLowerBounds() const { return glm::vec3(x, y, 0); }
  glm::vec3 GetUpperBounds() const { return glm::vec3(maxx, maxy, 0); }

};


#endif