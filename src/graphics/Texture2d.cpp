#include "Texture2d.hpp"
#include "utils/GLDebug.hpp"
unsigned int Texture2d::m_nextId = 0;

Texture2d::
Texture2d(GLuint _gltex, int _width, int _height, unsigned int* _data): m_uid(m_nextId++), 
    m_texture(_gltex), m_width(_width), m_height(_height), m_loaded(_data != nullptr) {}

Texture2d::
Texture2d(const Texture2d& _tex) {
    m_uid           = _tex.m_uid;
    m_texture       = _tex.m_texture;
    m_width         = _tex.m_width;
    m_height        = _tex.m_height;

    m_loaded        = _tex.m_loaded;
}

Texture2d
Texture2d::
operator= (const Texture2d& _tex) {
    m_uid           = _tex.m_uid;
    m_texture       = _tex.m_texture;
    m_width         = _tex.m_width;
    m_height        = _tex.m_height;
    m_loaded        = _tex.m_loaded;
    return *this;
}

void
Texture2d::
Bind() const {
    glBindTexture(GL_TEXTURE_2D, m_texture);
}

    