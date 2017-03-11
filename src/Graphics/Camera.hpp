#ifndef CAMERA_HPP_
#define CAMERA_HPP_

#include <memory>
#include <iostream>
#define GLM_FORCE_RADIANS
#include <glm/gtc/matrix_transform.hpp>
#include <glm/glm.hpp>

#include "Utilities/MatrixStack.hpp"

class MatrixStack;

class Camera {

  public:

    enum {
      ROTATE = 0,
      TRANSLATE,
      SCALE
    };

    Camera() {}

    ~Camera() {}

    // Initialize and setup camera values.
    void SetInitDistance(float _dist) { m_translation.z = -std::abs(_dist); }

    void SetAspect(float _aspect) { m_aspect = _aspect; };

    void SetRotationFactor(float _factor) { m_rfactor = _factor; };

    void SetTranslationFactor(float _factor) { m_tfactor = _factor; };

    void SetScaleFactor(float _factor) { m_sfactor = _factor; };

    void MouseClicked(float _x, float _y, bool _shift, bool _ctrl, bool _alt);

    void MouseMoved(float _x, float _y);

    // Unused for now.
    void ApplyProjectionMatrix(MatrixStack& _ms) const;

    void ApplyViewMatrix(MatrixStack& _ms) const;

    glm::mat4 GetProjection(); 
  private:

    int m_state;

    float m_aspect{1.};

    float m_fovy{45.};
    float m_znear{.1};
    float m_zfar{1000.};

    glm::vec2 m_rotation{0., 0.};
    glm::vec3 m_translation{0., 0., -5.};
    glm::vec2 m_mousePrev;

    float m_rfactor{.01};
    float m_tfactor{.001};
    float m_sfactor{.005};
};

#endif
