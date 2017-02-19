#include "Texture2d.hpp"

unsigned int Texture2d::m_nextId = 0;

Texture2d::
Texture2d(): m_uid(m_nextId++), m_width(0), m_height(0), m_intFormat(GL_RGB), 
    m_imgFormat(GL_RGB), m_wrapS(GL_REPEAT), m_wrapT(GL_REPEAT), m_filterMin(GL_LINEAR),
    m_filterMax(GL_LINEAR), m_loaded(false) {
    //glGenTextures(1, &m_texture);
}

Texture2d::
Texture2d(int _width, int _height, unsigned char* _data): m_uid(m_nextId++), 
    m_width(_width), m_height(_height), m_intFormat(GL_RGB), 
    m_imgFormat(GL_RGB), m_wrapS(GL_REPEAT), m_wrapT(GL_REPEAT), m_filterMin(GL_LINEAR),
    m_filterMax(GL_LINEAR) {
    
    glGenTextures(1, &m_texture);
    Generate(_width, _height, _data);
}

Texture2d::
Texture2d(const Texture2d& _tex) {
    m_uid           = _tex.m_uid;
    m_texture       = _tex.m_texture;
    m_width         = _tex.m_width;
    m_height        = _tex.m_height;

    m_intFormat     = _tex.m_intFormat;
    m_imgFormat     = _tex.m_imgFormat;

    m_wrapS         = _tex.m_wrapS;
    m_wrapT         = _tex.m_wrapT;
    m_filterMin     = _tex.m_filterMin;
    m_filterMax     = _tex.m_filterMax;
    m_loaded        = _tex.m_loaded;
}

Texture2d
Texture2d::
operator= (const Texture2d& _tex) {
    m_uid           = _tex.m_uid;
    m_texture       = _tex.m_texture;
    m_width         = _tex.m_width;
    m_height        = _tex.m_height;

    m_intFormat     = _tex.m_intFormat;
    m_imgFormat     = _tex.m_imgFormat;

    m_wrapS         = _tex.m_wrapS;
    m_wrapT         = _tex.m_wrapT;
    m_filterMin     = _tex.m_filterMin;
    m_filterMax     = _tex.m_filterMax;
    m_loaded        = _tex.m_loaded;
    return *this;
}

bool
Texture2d::
Generate(int _width, int _height, unsigned char* _data) {
    glBindTexture(GL_TEXTURE_2D, m_texture);
    glTexImage2D(GL_TEXTURE_2D, 0, m_intFormat, m_width, m_height, 0,
        m_imgFormat, GL_UNSIGNED_BYTE, _data);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, m_wrapS);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, m_wrapT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, m_filterMin);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, m_filterMax);

    glBindTexture(GL_TEXTURE_2D, 0);
    m_loaded = true;
    return m_loaded;
}

void
Texture2d::
Bind() const {
    glBindTexture(GL_TEXTURE_2D, m_texture);
}
