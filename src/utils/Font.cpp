#include "Font.hpp"
#include "GLDebug.hpp"
#include <fstream>
#include <iostream>
#include <sstream>

extern "C" {
	#define STB_TRUETYPE_IMPLEMENTATION
	#include "stb_truetype.h"
}

Font::Glyph::
Glyph(GLuint _tex, const glm::ivec2& _size, int _adv, int _stride):
	m_textureId(_tex), m_size(_size), m_advance(_adv), m_stride(_stride) {}

Font::Glyph::
Glyph(GLuint _tex, const glm::ivec2& _size, 
	const glm::ivec2& _bearing, int _adv): m_textureId(_tex),
	m_size(_size), m_bearing(_bearing), m_advance(_adv), m_stride(0){}

Font::
Font(const std::string& _filename, int _height, int _scale, int _ascent, int _descent, int _lineGap): m_height(_height),
	m_scale(_scale),m_ascent(_ascent), m_descent(_descent), m_lineGap(_lineGap) {
		// Geting the name of the file which is the name of font.
		// NOTE(ANDREW); Not multiplatform
		size_t pos = _filename.find_last_of('/');
		if(pos == std::string::npos) {
			// this is a big error;
			std::cout << "Error: Failed to locate a filename" << std::endl;
			// TODO(ANDREW): this should be an excpetion
		}
		else {
			m_fontName = _filename.substr(pos + 1, _filename.size() - 4);
			m_path = _filename.substr(0, pos);
		}
}

Font*
Font::
LoadFont(const std::string& _filename, int _height) {
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	// Loading the entire file
	std::string buffer;
	std::ifstream ff(_filename.c_str());
	if(ff) {
		std::stringstream ss;
		ss << ff.rdbuf(); 
		buffer = ss.str(); 
		ff.close();
	}
	else {
		std::cout << "Error: Failed to load file: '" << _filename << "'" << std::endl;
		return nullptr;
	}
	unsigned char* buf = (unsigned char*) buffer.c_str();

	// Creating a new font

	stbtt_fontinfo info;
	//int offset = stbtt_GetFontOffsetForIndex(buf, 0);
	if(!stbtt_InitFont(&info, buf, 0)) {
		std::cout << "Error: Failed to load: " << _filename << std::endl;
		return nullptr;
	}



	// Gets the scale for the font for the given height
	float scale = stbtt_ScaleForPixelHeight(&info, _height);

	int ascent, descent, lineGap;
	stbtt_GetFontVMetrics(&info, &ascent, &descent, &lineGap);
	Font* font = new Font(_filename, _height, scale, ascent, descent, lineGap);
	for(int i = 0; i < 128; ++i) {

		unsigned char* bitmap = nullptr;	
		int w, h, x, y;
		int advance, stride;
		GLuint texId;
		if(i == (int) ' ') {
			stbtt_GetGlyphHMetrics(&info, i, &advance, &stride);
			stbtt_GetCodepointBitmap(&info, 0.0f, scale, i, &w, &h, &x, &y);
			Font::Glyph glyph(texId, glm::ivec2(w,h), advance, stride);
			font->AddGlyph((GLchar) i, glyph);
			continue;
		}
		// gets the bitmap of the given character
		bitmap = stbtt_GetCodepointBitmap(&info, 0.0f, scale, i, &w, &h, &x, &y);
		if(!bitmap) {
			//std::cout << "Error: Failed to get bitmap: '" << (char) i << "'" << std::endl;
			continue;
		}
		// Gets the advance and stride for i.
		stbtt_GetGlyphHMetrics(&info, i, &advance, &stride);

		// Generates the Texture
		glGenTextures(1, &texId);
		if(texId == (GLuint) -1) {
			std::cout << "Error: OpenGL: Failed to generate texture buffer" << std::endl;
			continue;
		}
		glBindTexture(GL_TEXTURE_2D, texId);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, w, h, 0, GL_RED, GL_UNSIGNED_BYTE, bitmap);
		glCheckError();

		// texture parameters
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glCheckError();

		//Font::Glyph glyph(texId, glm::ivec2(w,h), glm::ivec2(), advance);
		Font::Glyph glyph(texId, glm::ivec2(w,h), advance, stride);
		font->AddGlyph((GLchar) i, glyph);
		//texId = -1;

		// NOTE(Andrew): Maybe the bitmap can be deleted
		bitmap = nullptr;
	}
	return font;
}

void
Font::
AddGlyph(GLchar _ch, const Glyph& _glyph) {
	m_glyphs.emplace(_ch, _glyph);
}

Font::Glyph* 
Font::
GetGlyph(GLchar _ch) {
	auto glyph = m_glyphs.find(_ch);
	if(glyph == m_glyphs.end()) {
		return nullptr;
	}
	return &glyph->second;
}