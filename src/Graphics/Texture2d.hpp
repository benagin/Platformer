///////////////////////////////////////////////////////////////////////////////
/// @name Texture2D
/// @group NA
/// @Author Andrew Bregger 18/02/2017
///
/// @brief A 2D texture.
///////////////////////////////////////////////////////////////////////////////
#ifndef TEXTURE_2D_HPP_
#define TEXTURE_2D_HPP_

#include <GL/glew.h>
#include <string>

#include <string>

/// @brief Texture2D representation.
class Texture2D {

    public:
        /////////////////////////////////////////////////////////////////////////////
        /// @name Constructors
        /// @{

        /// @brief Font Constructor
        /// @param _gltex The gl texture buffer.
        /// @param _width The width of the texture
        /// @param _height The height of the textre
        /// @param _data The data of the texture.
        Texture2D(GLuint _gltex, int _width, int _height, unsigned int* _data);

        /// @brief Copy Constrcutor
        Texture2D(const Texture2D& _tex);

        /// @brief Copy operator
        Texture2D operator= (const Texture2D& _tex);

        /// @}
        /// @name Operators
        /// @{

        /// @brief Binds the texture to the current texture object.
        void Bind() const;

        /// @brief Binds the texture to the current texture object.
        void Unbind() const;

        /// @brief Whether a texture is loaded
        bool IsLoaded() { return m_loaded; }

        /// @brief Width of the Texture
        int GetWidth() { return m_width; }

        /// @brief Height of the Texture.
        int GetHeight() { return m_height; }

         /// @bried Which gl texture is this.
        void SetUnit(unsigned int _unit) { m_unit = _unit;}

        unsigned int GetUnit() { return m_unit; }

        unsigned int* GetData() const { return m_data; }

        /// @}
    private:

    unsigned int m_uid;             ///< Id of the texture, this might be needed.
    unsigned int m_texture;         ///< Opengl texture id
    int m_width;                    ///< Width of the image
    int m_height;                   ///< Height of the image.
    bool m_loaded;                  ///< Says whether a texture is loaded intot he buffer
    unsigned int m_unit;
    unsigned int* m_data;           ///< Raw texture data.
    static unsigned int m_nextId;   ///< used the next id
};

#endif
