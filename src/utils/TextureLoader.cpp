#include "TextureLoader.hpp"
#include <iostream>

extern "C" {
	#define STB_IMAGE_IMPLEMENTATION
	
	/// NOTE(ANDREW): 18/02/2017
	/// For now we only can load JPEG and PNG
	/// Others can be added if we need them.
  //#define STBI_ONLY_JPEG
  //#define STBI_ONLY_PNG

	#include "stb_image.h"
}

Texture2d
TextureLoader::
operator() (const std::string& _filename) {
	return Load(_filename);
}

Texture2d
TextureLoader::
Load(const std::string& _filename) {
	int x, y, channels;
	std::cout << _filename << std::endl;
	unsigned char* data = stbi_load(_filename.c_str(), &x, &y, &channels, STBI_rgb);
	std::cout << "Channels: " << channels << std::endl;
	std::cout << "Height: " << y << "\nWidth: " << x << std::endl;
	if(!data) {
		std::cout << stbi_failure_reason() << std::endl;
		return Texture2d();	
	}
	std::cout << "Texture Loaded" << std::endl;
	Texture2d tex(x,y, data);
	// tex.SetInternalFormat(GL_RGBA, true);
	stbi_image_free(data);
	return tex;
}