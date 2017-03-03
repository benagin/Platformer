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

        /// @brief Font Constructor
        /// @param _gltex The gl texture buffer.
        /// @param _width The width of the texture
        /// @param _height The height of the textre
        /// @param _data The data of the texture.
        Texture2d(GLuint _gltex, int _width, int _height, unsigned int* _data);

        /// @brief Copy Constrcutor
        Texture2d(const Texture2d& _tex);

        /// @brief Copy operator
        Texture2d operator= (const Texture2d& _tex);

        /// @}
        /// @name Operators
        /// @{

        /// @brief Binds the texture to the current texture object.
        void Bind() const;

        /// @brief Whether a texture is loaded
        bool IsLoaded() { return m_loaded; }

        int GetWidth() { return m_width; }
        int GetHeight() { return m_height; }

        /// @}
    private:

    unsigned int m_uid;             ///< Id of the texture, this might be needed.
    unsigned int m_texture;         ///< Opengl texture id
    int m_width;                    ///< Width of the image
    int m_height;                   ///< Height of the image.

    bool m_loaded;                  ///< Says whether a texture is loaded intot he buffer
    unsigned int* m_data;           ///< Raw texture data.
    static unsigned int m_nextId;   ///< used the next id
};

#endif