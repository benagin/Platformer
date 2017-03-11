#include "Resources.hpp"
#include <tinyxml2.h>

using namespace tinyxml2;

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
AddTexture(const string& _name, Texture2D* _texture) {
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

Texture2D*
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
  tinyxml2::XMLDocument xmlDoc;
  Resources* rsc = new Resources;
  xmlDoc.LoadFile(_file.c_str());
  std::string base;

  XMLElement* root = xmlDoc.RootElement();
  const char* basefile = root->Attribute("basefile");
  base = std::string(basefile);

  XMLElement* child = root->FirstChild()->ToElement();
  while(child != nullptr) {
    std::string title(child->Value());
    auto name = std::string(child->Attribute("name"));
    const char* d = child->Attribute("default");

    if(title == "Shader") {
      std::string path = base + "shaders/";
      auto vertex = std::string(child->Attribute("vertex"));
      auto fragment = std::string(child->Attribute("fragment"));
      std::cout << "Loaded Shader: " << name << "\n";
      std::cout << "\t" << vertex << std::endl;
      std::cout << "\t" << fragment << std::endl;
      Shader* s = new Shader(path + vertex, path + fragment);
      rsc->AddShader(name, s);
    }
    else if(title == "Texture") {
      std::string path = base + "textures/";
      auto file = std::string(child->Attribute("file"));
      std::cout << "Loaded Texture: " << name << "\n";
      std::cout << "\t" << file << std::endl;
      Texture2D* t = textureLoader.LoadPtr(path + file);
      rsc->AddTexture(name, t);
    }
    else if(title == "Font") {
      std::string path = base + "fonts/";
      auto file = std::string(child->Attribute("file"));
      int height = child->IntAttribute("height");
      std::cout << "Loaded Font: " << name << "\n";
      std::cout << "\t" << file << std::endl;
      Font* f = fontLoader.Load(path + file, height);
      rsc->AddFont(name, f);
    }

    std::cout << "\tDefault: ";
    if(d) {
      std::cout << d << std::endl;
    }
    else {
      std::cout << "False\n";
    }
    auto t = child->NextSibling();
    if(t)
      child = t->ToElement();
    else
      child = nullptr;
  }



  return rsc;
}

Font* 
Resources::
GetFont() {
  return m_instance->m_fonts.begin()->second;
}
