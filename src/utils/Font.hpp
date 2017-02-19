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

#include <GL/glew.h>
#include <glm/glm.hpp>


/// @brief A representation of a font.
/// @note It is only the first 128 characters for now.
class Font {

  public:

    class Glyph {

      public:
        ///////////////////////////////////////////////////////////////////////////
        /// @brief Representation of a single Glyph, ie. character
        Glyph(GLuint _tex, const glm::ivec2& _size,
            int _adv, int _stride);


        Glyph(GLuint _tex, const glm::ivec2& _size,
            const glm::ivec2& _bearing, int _adv);

        int GetStride() { return m_stride; }
        int GetAdvance() { return m_advance; }
        float GetWidth() { return m_size.x; }
        float GetHeight() { return m_size.y; }
        float GetBearingX() { return m_bearing.x; }
        float GetBearingY() { return m_bearing.y; }
        GLuint GetTexture() { return m_textureId; }

      private:

        GLuint m_textureId;   ///< the opengl texture id
        glm::ivec2 m_size;    ///< the width and height of the texture
        glm::ivec2 m_bearing; ///< x and y bearing of the glyph
        int m_advance;        ///< the distance in the x until the next character
        int m_stride; 	      ///< X bearing
    };

    /////////////////////////////////////////////////////////////////////////////
    /// @name Constructors
    /// @{

    /// @brief Font Constructor
    /// @param _name the filename path of the font file
    /// @param _height Height of the Font
    /// @param _scale Scaling of the Font.
    Font(const std::string& _name, int _height, int _scale,
        int _ascent, int _descent, int _lineGap);

    /// @brief Font destructor
    ~Font() = default;

    /// @}
    /// @name Accessors	and Manipulators
    /// @{
    int GetHeight() { return m_height; }

    int GetScale() { return m_scale; }

    float GetYAdvance() { return (m_ascent - m_descent + m_lineGap) * m_scale; }

    Glyph* GetGlyph(GLchar _ch);
    /// @}
    /// @name Loaders
    /// @{
    /////////////////////////////////////////////////////////////////////////////
    /// @brief Loads a font from a file.
    /// @param _filename the full path of the font file
    /// @param _height height of the rendered glyphs
    ///
    /// @note For now we assume the filename in ttf file format
    static Font* LoadFont(const std::string& _filename, int _height);

    /// @}

  private:
    /////////////////////////////////////////////////////////////////////////////
    /// @brief Adds glyph to the map
    /// @param _ch The character
    /// @param _glyph The glyph associated with _ch.
    void AddGlyph(GLchar _ch, const Glyph& _glyph);

    int m_height; ///< Height of the glyphs
    int m_scale;  ///< Scaling using to generate the glyphs
                  ///< (this might not be needed)
    int m_ascent;
    int m_descent;
    int m_lineGap;

    std::string m_fontName; ///< The name of the font: i.e: ariel.ttf with be ariel.
    std::string m_path; ///< the path to the font.
    std::map<GLchar, Glyph> m_glyphs; ///< Map fo characters to the glyph data.
};

#endif
