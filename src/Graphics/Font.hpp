///////////////////////////////////////////////////////////////////////////////
/// @name Font
/// @group NA
/// @Author Andrew Bregger 17/02/2017
///
/// @brief Represents a font that is able to be rendered.
///         Uses stb_truetype: Sean Barret
///////////////////////////////////////////////////////////////////////////////

#ifndef FONT_HPP_
#define FONT_HPP_

#include <map>
#include <string>
#include "Texture2D.hpp"

#include <GL/glew.h>
#include <glm/glm.hpp>


/// @brief A representation of a font.
/// @note It is only the first 128 characters for now.
class Font {

  public:

    class Glyph : public Texture2D {

      public:
        ///////////////////////////////////////////////////////////////////////////
        /// @brief Representation of a single Glyph, ie. character
        Glyph(GLuint _tex, const glm::ivec2& _size,
            const glm::ivec2& _bearing, int _adv, unsigned int* _data);
            
        int GetAdvance() { return m_advance; }
        float GetBearingX() { return m_bearing.x; }
        float GetBearingY() { return m_bearing.y; }
      private:
        glm::ivec2 m_bearing; ///< x and y bearing of the glyph
        int m_advance;        ///< the distance in the x until the next character
    };

    /////////////////////////////////////////////////////////////////////////////
    /// @name Constructors
    /// @{

    /// @brief Font Constructor
    /// @param _name the filename path of the font file
    /// @param _height Height of the Font
    /// @param _scale Scaling of the Font.
    Font(const std::string& _name, int _height);

    /// @brief Font destructor
    ~Font() = default;

    /// @}
    /// @name Accessors	and Manipulators
    /// @{
    int GetHeight() { return m_height; }

    Glyph* GetGlyph(GLchar _ch);
    /// @}

  private:
    /////////////////////////////////////////////////////////////////////////////
    /// @brief Adds glyph to the map
    /// @param _ch The character
    /// @param _glyph The glyph associated with _ch.
    void AddGlyph(GLchar _ch, const Glyph& _glyph);

    int m_height; ///< Height of the glyphs

    std::string m_fontName; ///< The name of the font: i.e: ariel.ttf with be ariel.
    std::string m_path; ///< the path to the font.
    std::map<GLchar, Glyph> m_glyphs; ///< Map fo characters to the glyph data.
    friend class FontLoader;
};

#endif
