///////////////////////////////////////////////////////////////////////////////
/// @name FontLoader
/// @group NA
/// @Author Ben Smith 16/02/2017
///
/// @brief Loads a Font from a ttf file and stores the glyphs
///         Uses TrueType
///////////////////////////////////////////////////////////////////////////////
#ifndef FT_LOADER_HPP_
#define  FT_LOADER_HPP_

#include <iostream>
#include <string>
#include <map>

#include <ft2build.h>
#include FT_FREETYPE_H

#include <GL/glew.h>
#include <glm/glm.hpp>

#include <string>

/// Most of this code comes from:
/// https://learnopengl.com/#!In-Practice/Text-Rendering

/// Replace this with the path to your fonts. This folder should contain various
/// .ttf files.
#define ROBOTO "../assets/fonts/Roboto-Light.ttf"

class Font;


////////////////////////////////////////////////////////////////////////////////
/// @brief FontLoader is used to load and perform necessary operations for the
///        freetype 2.7 library. This allows text rendering.
class FontLoader {

  public:

    FontLoader() = default;

    ~FontLoader();

    Font* Load(const std::string& _path, int _height);

    // Load each character from the font face and add it to the characters map.
    Font* LoadCharacters(FT_Face& _face, Font* _font);
  private:

    FT_Library m_ft{nullptr}; ///< Main FreeType object.

    FT_Face m_face {nullptr}; ///< Font face object
};

#endif
