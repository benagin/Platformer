#ifndef GUI_HPP_
#define GUI_HPP_

#include <iostream>
#include <vector>
#include <string>
#include <tinyxml2.h>

#include "GUIElement.hpp"

class GUI {

  public:

    GUI() {}

    // Construct with an XML file.
    GUI(std::string _filename);

    ~GUI() {}

    enum {
      StartMenu,
      HUD,
      EndMenu
    };

    void Draw(const Shader& _shader) const;

    void MouseClicked(glm::dvec2 _location);

  private:

    tinyxml2::XMLDocument m_xmlDoc;

    std::vector<GUIElement> m_elements;
};

#endif
