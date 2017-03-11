#include "GUI.hpp"


GUI::
GUI(std::string _filename) {
  m_xmlDoc.LoadFile(_filename.c_str());

  const auto title = m_xmlDoc.FirstChildElement("StartMenu");

  std::cout << "Name: " << title << std::endl;
}

void
GUI::
Draw(const Shader& _shader) const {
  for(const auto& e : m_elements)
    e.Draw(_shader);
}


void
GUI::
MouseClicked(glm::dvec2 _location) {

}
