#include "Resources.hpp"


Resources* Resources::m_instance = nullptr;
Resources::
Resources() {
  if(m_instance) {
    std::cout << "Error: Instanciating Multiple Resources" << std::endl;
  }
  m_instance = this;
}


Resources::
~Resources() {

}


void
Resources::
AddFont(const string& _name, Font* _font) {
  m_fonts.emplace(_name, _font);
}

void
Resources::
AddTexture(const string& _name, Texture2d* _texture) {
  m_textures.emplace(_name, _texture);
}

void
Resources::
AddShader(const string& _name, Shader* _shader) {
  m_shaders.emplace(_name, _shader);
}


Font*
Resources::
GetFont(const string& _name) {
  return m_fonts[_name];
}

Texture2d*
Resources::
GetTexture(const string& _name) {
  return m_textures[_name];
}

Shader*
Resources::
GetShader(const string& _name) {
  return m_shaders[_name];
}

Resources*
Resources::
Get() {
  return m_instance;
}

Resources*
Resources::
Init(const string& _file) {
  FontLoader fontLoader;
  TextureLoader textureLoader;

  Resources* rsc = new Resources;
  std::ifstream r(_file);
  std::stringstream ss;
  ss << r.rdbuf();
  r.close();

  string temp;
  string base_path = "./";
  string name;

  while(ss >> temp) {
    if(temp == "b") {
      ss >> base_path;
    }
    else if(temp == "s") {
      // shader
      ss >> name;
      string frag, vertex;
      ss >> vertex;
      ss >> frag;
      vertex = base_path + "shaders/" + vertex;
      frag = base_path + "shaders/" + frag;
      std::cout << "Loaded Shader: " << name << " vertex: " << vertex << " fragment: " << frag << std::endl;
      Shader* s = new Shader(vertex, frag);
      rsc->AddShader(name, s);
    }
    else if(temp == "t") {
      // texture
      ss >> name;
      string file;
      ss >> file;
      file = base_path + "textures/" + file;
      std::cout << "Loaded Texture: " << name << " File: " << file << std::endl;
      Texture2d* t = textureLoader.LoadPtr(file);
      rsc->AddTexture(name, t);
    }
    else if(temp == "f") {
      // font
      ss >> name;
      string file;
      string size;
      ss >> file;
      ss >> size;
      file = base_path + "fonts/" + file;
      int s = atoi(size.c_str());
      std::cout << "Loaded Font: " << name << " File: " << file << " Size: " << size << std::endl;
      Font* font = fontLoader.Load(file, s);
      rsc->AddFont(name, font);
    }
  }
  return rsc;
}
