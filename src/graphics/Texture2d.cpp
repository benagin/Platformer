#include "Texture2d.hpp"

unsigned int Texture2d::m_nextId = 0;

Texture2d::
Texture2d(): m_uid(m_nextId++), m_width(0), m_height(0), m_intFormat(GL_RGB), 
    m_imgFormat(GL_RGB), m_wrapS(GL_REPEAT), m_wrapT(GL_REPEAT), m_filterMin(GL_LINEAR),
    m_filterMax(GL_LINEAR) {
    
    glGenTextures(1, &m_texture);
}

Texture2d::
Texture2d(int _width, int _height, unsigned char* _data): m_uid(m_nextId++), 
    m_width(_width), m_height(_height), m_intFormat(GL_RGB), 
    m_imgFormat(GL_RGB), m_wrapS(GL_REPEAT), m_wrapT(GL_REPEAT), m_filterMin(GL_LINEAR),
    m_filterMax(GL_LINEAR) {
    
    glGenTextures(1, &m_texture);
    Generate(_width, _height, _data);
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
    return true;
}

void
Texture2d::
Bind() const {
    glBindTexture(GL_TEXTURE_2D, m_texture);
}