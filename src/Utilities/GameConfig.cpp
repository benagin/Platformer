#include "GameConfig.hpp"

GameConfig::
GameConfig(const std::string& _path) {
  m_parser = new INIParser(_path);
  m_parser->Parse();
}
