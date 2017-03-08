#ifndef INI_PARSER_HPP_
#define INI_PARSER_HPP_
#include <string>
#include <unordered_map>

class INIParser {
public:
	INIParser(const std::string& _path);
	void Parse();

	int GetFieldInt(const std::string& _section, const std::string& _property);
	float GetFieldIntFloat(const std::string& _section, const std::string& _property);
	std::string GetField(const std::string& _section, const std::string& _property);
private:
	std::string m_path;
	typedef std::unordered_map<std::string, std::string> Data;
	typedef std::unordered_map<std::string, Data> ConfigData;
	ConfigData m_data;
};

#endif // INI_PARSER_HPP_
