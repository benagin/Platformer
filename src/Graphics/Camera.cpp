#include "Camera.hpp"


void
Camera::
MouseClicked(float _x, float _y, bool _shift, bool _ctrl, bool _alt) {
  m_mousePrev.x = _x;
  m_mousePrev.y = _y;

  // Set the state depending on the modifier being pressed.
  if(_shift) {
    m_state = Camera::TRANSLATE;
  }
  else if(_ctrl) {
    m_state = Camera::SCALE;
  }
  else {
    m_state = Camera::ROTATE;
  }
}

void
Camera::
MouseMoved(float _x, float _y) {
  // Get direction from previous to current mouse position.
  glm::vec2 mouseCurr(_x, _y);
  glm::vec2 dv = mouseCurr - m_mousePrev;

  switch(m_state) {
    case Camera::ROTATE:
      m_rotation+= m_rfactor * dv;
      break;

    case Camera::TRANSLATE:
      m_translation.x -= m_translation.z * m_tfactor * dv.x;
      m_translation.y += m_translation.z * m_tfactor * dv.y;
      break;

    case Camera::SCALE:
      m_translation.z *= (1.0f - m_sfactor * dv.y);
      break;
  }

  // Store this mouse position.
  m_mousePrev = mouseCurr;
}


void
Camera::
ApplyProjectionMatrix(MatrixStack& _ms) const {
  // Modify provided MatrixStack.
  _ms.multMatrix(glm::perspective(m_fovy, m_aspect, m_znear, m_zfar));
}


void
Camera::
ApplyViewMatrix(MatrixStack& _ms) const {
  _ms.translate(m_translation);
  _ms.rotate(m_rotation.y, glm::vec3(1.0f, 0.0f, 0.0f));
  _ms.rotate(m_rotation.x, glm::vec3(0.0f, 1.0f, 0.0f));
}
