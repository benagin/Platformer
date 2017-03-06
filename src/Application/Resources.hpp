#ifndef RESOURCES_HPP_
#define RESOURCES_HPP_

#include <string>
#include <map>
#include <iostream>
#include <cstdlib>
#include <fstream>
#include <sstream>

#include "Utils/FontLoader.hpp"
//#include "Utils/TextureLoader.hpp"
#include "Graphics/Texture2d.hpp"
#include "Graphics/Font.hpp"
#include "Graphics/Shader.hpp"

using std::map;
using std::string;

class Font;
class Texture2d;
class Shader;

class Resources {

  public:

    Resources();
    ~Resources();

    void AddFont(const string& _name, Font* _font);
    void AddTexture(const string& _name, Texture2d* _texture);
    void AddShader(const string& _name, Shader* _shader);

    Font* GetFont(const string& _name);
    Texture2d* GetTexture(const string& _name);
    Shader* GetShader(const string& _name);
    static Resources* Get();
    static Resources* Init(const string& _file);

  private:

    map<string, Font*> m_fonts;
    map<string, Texture2d*> m_textures;
    map<string, Shader*> m_shaders;
    static Resources* m_instance;
};

#endif
