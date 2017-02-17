#ifndef FT_LOADER_HPP_
#define  FT_LOADER_HPP_

#include <iostream>
#include <string>
#include <map>

#include <ft2build.h>
#include FT_FREETYPE_H

#include <GL/glew.h>
#include <glm/glm.hpp>

/// Most of this code comes from:
/// https://learnopengl.com/#!In-Practice/Text-Rendering

/// Replace this with the path to your fonts. This folder should contain various
/// .ttf files.
#define ROBOTO "../assets/fonts/Roboto-Light.ttf"


////////////////////////////////////////////////////////////////////////////////
/// @brief FTLoader is used to load and perform necessary operations for the
///        freetype 2.7 library. This allows text rendering.
class FTLoader {

  public:

    FTLoader();

    ~FTLoader();

    // Load each character from the font face and add it to the characters map.
    void LoadCharacters(FT_Face& _face);

    // Store metrics for each character in a font face.
    struct Character {
      GLuint m_textureID;   ///< Id for the glyph texture.
      glm::ivec2 m_size;
      glm::ivec2 m_bearing; ///< Offest from baseline to left/top of glyph.
      GLuint m_advance;     ///< Offset to advance to next glyph.
    };

  private:

    FT_Library m_ft{nullptr}; ///< Main FreeType object.

    FT_Face m_roboto{nullptr}; ///< Font face object for Roboto-Light.

    std::map<GLchar, Character> m_robotoChars; ///< Store 128 ASCII characters.
};

#endif
