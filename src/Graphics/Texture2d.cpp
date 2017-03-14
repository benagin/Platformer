#include "Utilities/GLDebug.hpp"
#include "Texture2D.hpp"
unsigned int Texture2D::m_nextId = 0;

Texture2D::
Texture2D(GLuint _gltex, int _width, int _height, unsigned int* _data): m_uid(m_nextId++),
    m_texture(_gltex), m_width(_width), m_height(_height), m_loaded(_data != nullptr), m_unit(0) {}

Texture2D::
Texture2D(const Texture2D& _tex) {
    m_uid           = _tex.m_uid;
    m_texture       = _tex.m_texture;
    m_width         = _tex.m_width;
    m_height        = _tex.m_height;
    m_unit          = _tex.m_unit;
    m_loaded        = _tex.m_loaded;
}

Texture2D
Texture2D::
operator= (const Texture2D& _tex) {
    m_uid           = _tex.m_uid;
    m_texture       = _tex.m_texture;
    m_width         = _tex.m_width;
    m_height        = _tex.m_height;
    m_loaded        = _tex.m_loaded;
    return *this;
}

void
Texture2D::
Bind() const {
    glBindTexture(GL_TEXTURE_2D, m_texture);
    glActiveTexture(GL_TEXTURE0 + m_unit);
    glCheckError();
}


void
Texture2D::
Unbind() const {
    glActiveTexture(GL_TEXTURE0 + m_unit);
    glBindTexture(GL_TEXTURE_2D, 0);
    glCheckError();
}