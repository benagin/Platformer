///////////////////////////////////////////////////////////////////////////////
/// @name TextureLoader
/// @group NA
/// @Author Andrew Bregger 18/02/2017
///
/// @brief Loads a texture from an image. PNG, JPEG and others.
/// 				Uses stb_image: Sean Barret
///////////////////////////////////////////////////////////////////////////////
#ifndef TEXTURE_LOADER_HPP_
#define TEXTURE_LOADER_HPP_

#include <string>
#include <iostream>
#include <cassert>
#include <glm/glm.hpp>

#include "Graphics/Texture2d.hpp"


class TextureLoader {

public:
	////////////////////////////////////////////////////////////////////////
	/// @name Constructors and Destructors
	/// @{

	TextureLoader() = default;
	~TextureLoader() = default;

	/// @}
	/// @name Operators
	/// @{
	/// @brief Operator for loading a Texture
	/// @param _filename The path name to the image.
	/// @return The new texture
	Texture2d operator() (const std::string& _filename);

	/// @brief Another interface for creating a texture
	/// @param _filename The path name to the image.
	/// @return The new texture
	Texture2d Load(const std::string& _filename);

	/// @brief Another interface for creating a texture
	/// @param _filename The path name to the image.
	/// @return The new texture	pointer
	Texture2d* LoadPtr(const std::string& _filename);

	/// @}
	/// @name Delete Operators and constructors
	/// @{

	TextureLoader(const TextureLoader&) = delete;
	TextureLoader operator= (const TextureLoader&) = delete;

	/// @}

private:

};


#endif
