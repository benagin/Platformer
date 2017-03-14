#include "TextureLoader.hpp"

#include <glm/glm.hpp>
extern "C" {
	#define STB_IMAGE_IMPLEMENTATION
	#include "Utilities/stb_image.h"
}

Texture2D
TextureLoader::
operator() (const std::string& _filename) {
	return Load(_filename);
}


Texture2D
TextureLoader::
Load(const std::string& _filename) {
	/*
	int x, y, channels;
	Texture2D tex; // = Texture2D();
	unsigned int* data = (unsigned int*) stbi_load(_filename.c_str(), &x, &y, &channels, STBI_rgb_alpha);


	if(!data) {
		std::cout << stbi_failure_reason() << std::endl;
		return Texture2D();	
	}

	if(channels == 4) {
		tex.SetInternalFormat(GL_RGBA);
		tex.SetImageFormat(GL_RGBA);
	}

	tex.Generate(x, y, data);
	*/
	return Texture2D(-1, 0, 0, nullptr);
}

Texture2D* 
TextureLoader::
LoadPtr(const std::string& _filename) {
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glPixelStorei(GL_UNPACK_ROW_LENGTH, 0);
	glPixelStorei(GL_UNPACK_SKIP_PIXELS, 0);
	glPixelStorei(GL_UNPACK_SKIP_ROWS, 0);
	int x, y, channels;
	// stbi_set_flip_vertically_on_load(1);
	unsigned char* data = stbi_load(_filename.c_str(), &x, &y, &channels, STBI_rgb_alpha);
	if(!data) {
		std::cout << stbi_failure_reason() << std::endl;
		return nullptr;
	}
	GLuint texture;
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	if(channels == 4)
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, x, y, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
	else if(channels == 3)
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, x, y, 0, GL_RGB, GL_UNSIGNED_BYTE, data);

	glGenerateMipmap(GL_TEXTURE_2D);
	//stbi_image_free(data);

	return new Texture2D(texture, x, y, (unsigned int*) data);
}
