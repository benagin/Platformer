#include "FTLoader.hpp"


FTLoader::
FTLoader() {
  m_ft = FT_Library();

  if(FT_Init_FreeType(&m_ft))
    std::cerr << "Could not init FreeType Library (FTLoader Constructor)" <<
      std::endl;

  m_roboto = FT_Face();

  // ROBOTO is defined in the header as the path to the Roboto-Light.ttf file.
  if(FT_New_Face(m_ft, ROBOTO, 0, &m_roboto))
    std::cerr << "Failed to load font (Roboto-Light)." << std::endl;

  FT_Set_Pixel_Sizes(m_roboto, 0, 48);

  LoadCharacters(m_roboto);
}


FTLoader::
~FTLoader() {
  FT_Done_Face(m_roboto);
  FT_Done_FreeType(m_ft);
}


void
FTLoader::
LoadCharacters(FT_Face& _face) {
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

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, bitmap.width,
        bitmap.rows, 0, GL_RGB, GL_UNSIGNED_BYTE,
        bitmap.buffer);

    // Set texture options.
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    // Store character.
    Character character{texture, glm::ivec2(bitmap.width, bitmap.rows),
      glm::ivec2(glyph->bitmap_left, glyph->bitmap_top),
      static_cast<GLuint>(glyph->advance.x)};

    m_robotoChars.emplace(c, character);
  }
}
