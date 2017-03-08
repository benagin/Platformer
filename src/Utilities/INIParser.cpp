#include "INIParser.hpp"
#include <fstream>
#include <string>
#include <sstream>
#include <iostream>

INIParser::
INIParser(const std::string& _path) {
	m_path = _path;
}

void
INIParser::
Parse() {
	std::fstream config(m_path.c_str());
	std::string content;
	if(config) {
		std::stringstream ss;
		ss << config.rdbuf();
		content = ss.str();
	}
	else {
		std::cout << "Error: Config: Failed to load file: '" << m_path << "'" << std::endl;
		exit(1);
	}

	std::string currentSection;
	for(size_t i = 0; i < content.size(); ++i) {
		char ch = content.at(i);
		switch(ch) {
			case ';':
			case '#':
				while(content[i] != '\n')
					++i;
			break;
			case '[': {
				size_t start = ++i;
				while(content[i] != ']')
					++i;
				currentSection = content.substr(start, i - start);
				//m_data.emplace(section, Data());
			} break;
			case '\n':
				++i;
			default: {
				size_t start = i;
				while(content[i] != '\n')
					++i;
				std::string row = content.substr(start, i - start);
				size_t eq = row.find('=');
				std::string prop = row.substr(0, eq);
				std::string value = row.substr(eq + 1, content.size() - eq);
				m_data[currentSection].emplace(prop, value);
			}
		}

	}
}

int 
INIParser::
GetFieldInt(const std::string& _section, const std::string& _property) {
	return 0;
}

float 
INIParser::
GetFieldIntFloat(const std::string& _section, const std::string& _property) {
	return 0.0f;
}

std::string 
INIParser::
GetField(const std::string& _section, const std::string& _property) {
	return "";
}
