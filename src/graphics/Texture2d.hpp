///////////////////////////////////////////////////////////////////////////////
/// @name Texture2d
/// @group NA
/// @Author Andrew Bregger 18/02/2017
///
/// @brief A 2D texture.
///////////////////////////////////////////////////////////////////////////////
#ifndef TEXTURE_2D_HPP_
#define TEXTURE_2D_HPP_

#include <GL/glew.h>
#include <string>

/// @brief Texture2d representation.
class Texture2d {

    public:
        /////////////////////////////////////////////////////////////////////////////
        /// @name Constructors
        /// @{

        /// @brief Default Texture2d giving default values for texture representation.
        Texture2d();
        /// @brief Font Constructor
        /// @param _width The width of the texture
        /// @param _height The height of the textre
        /// @param _data The data of the texture.
        Texture2d(int _width, int _height, unsigned char* _data);

        /// @}
        /// @name Operators
        /// @{

        /// @brief Generates the gl texture representation.
        /// @param _width The width of the texture
        /// @param _height The height of the textre
        /// @param _data The data of the texture.
        bool Generate(int _width, int _height, unsigned char* _data);

        /// @brief Binds the texture to the current texture object.
        void Bind() const;

        /// @}
    private:

    unsigned int m_uid;             ///< Id of the texture, this might be needed.
    unsigned int m_texture;         ///< Opengl texture id
    int m_width;                    ///< Width of the image
    int m_height;                   ///< Height of the image.

    GLuint m_intFormat;             ///< Internal format.
    GLuint m_imgFormat;             ///< Image format.

    GLuint m_wrapS;                 ///< Wrap of the S axis 
    GLuint m_wrapT;                 ///< Wrap of the T asis
    GLuint m_filterMin;             ///< Im not sure. Needed though.
    GLuint m_filterMax;             ///< Im not sure. Needed though.
    static unsigned int m_nextId;   ///< used the next id
};

#endif