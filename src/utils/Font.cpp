#include "Font.hpp"
#include "GLDebug.hpp"
#include <fstream>
#include <iostream>
#include <sstream>

Font::Glyph::
Glyph(GLuint _tex, const glm::ivec2& _size, int _adv, int _stride) :
  m_textureId(_tex), m_size(_size), m_advance(_adv), m_stride(_stride) {}

Font::Glyph::
Glyph(GLuint _tex, const glm::ivec2& _size, const glm::ivec2& _bearing,
    int _adv) : m_textureId(_tex), m_size(_size), m_bearing(_bearing),
    m_advance(_adv), m_stride(0) {}

Font::
Font(const std::string& _filename, int _height): m_height(_height) {

  // Geting the name of the file which is the name of font.
  // NOTE(ANDREW); Not multiplatform
  size_t pos = _filename.find_last_of('/');
  if(pos == std::string::npos) {
    // this is a big error;
    std::cout << "Error: Failed to locate a filename" << std::endl;
    // TODO(ANDREW): this should be an excpetion
  }
  else {
    m_fontName = _filename.substr(pos + 1, _filename.size() - 4);
    m_path = _filename.substr(0, pos);
  }
}


void
Font::
AddGlyph(GLchar _ch, const Glyph& _glyph) {
  m_glyphs.emplace(_ch, _glyph);
}

Font::Glyph*
Font::
GetGlyph(GLchar _ch) {
  auto glyph = m_glyphs.find(_ch);

  if(glyph == m_glyphs.end()) {
    return nullptr;
  }

  return &glyph->second;
}
