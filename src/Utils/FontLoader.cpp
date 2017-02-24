#include "FontLoader.hpp"
#include "Font.hpp"

FontLoader::
~FontLoader() {}


Font*
FontLoader::
LoadCharacters(FT_Face& _face, Font* _font) {
  glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
  for(GLubyte c = 0; c < 128; c++) {

    // Load each character frome the font face.
    if(FT_Load_Char(_face, c, FT_LOAD_RENDER)) {
      std::cerr << "Failed to load Glyph." << std::endl;

      continue;
    }

    // Generate texture.
    GLuint texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);

    const auto glyph = _face->glyph;
    const auto bitmap = glyph->bitmap;

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, bitmap.width,
        bitmap.rows, 0, GL_RED, GL_UNSIGNED_BYTE,
        bitmap.buffer);

    // Set texture options.
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    // Store character.
    Font::Glyph character(texture, glm::ivec2(bitmap.width, bitmap.rows),
      glm::ivec2(glyph->bitmap_left, glyph->bitmap_top),
      static_cast<GLuint>(glyph->advance.x));

    _font->AddGlyph(c, character);
  }
  FT_Done_Face(m_face);
  FT_Done_FreeType(m_ft);

  return _font;
}

Font*
FontLoader::
Load(const std::string& _path, int _height) {
  assert(_height > 0);

  m_ft = FT_Library();

  if(FT_Init_FreeType(&m_ft))
    std::cerr << "Could not init FreeType Library (FontLoader Constructor)" <<
      std::endl;

  m_face = FT_Face();

  // ROBOTO is defined in the header as the path to the Roboto-Light.ttf file.
  if(FT_New_Face(m_ft, _path.c_str(), 0, &m_face))
    std::cerr << "Failed to load font " << _path << std::endl;

  FT_Set_Pixel_Sizes(m_face, 0, _height);

  Font* font = new Font(_path, _height);

  return LoadCharacters(m_face, font);
}
