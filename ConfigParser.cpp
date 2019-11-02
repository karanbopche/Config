// ConfigParser.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include "ConfigParser.h"

namespace config {

	bool Config::SelectSection(std::string sectionName) {
		// if key is present in map...
		if (sections.count(sectionName)) {
			selectedSection = sectionName;
			return true;
		}
		else {
			selectedSection = "";
			return false;
		}
	}

	bool Config::SaveFile(const char* filePath) {
		std::ofstream file(filePath);
		if (!file.is_open())
			return false;
		for (auto& s : sections) {
			file << "[" << s.first << "]" << std::endl;
			for (auto d : s.second.dataValues) {
				file << d.first << '=' << d.second << std::endl;
			}
			file << std::endl;
		}
		return true;
	}

	bool Config::LoadFile(const char* filePath) {
		std::ifstream file(filePath);
		std::string line;
		int lineNumber = 1;
		if (!file.is_open())
			return false;
		while (std::getline(file, line)) {
			if (line.empty())
				continue;
			RemoveWhiteSpaces(line);
			// comment lines...
			if (line[0] == '#' || line[0] == ';')
				continue;

			// remove afterline comments..
			line = line.substr(0, line.find(';'));
			line = line.substr(0, line.find('#'));

			// if DataValue line....
			if (line.find('=') != std::string::npos) {
				int splitLocation = line.find("=");
				std::string field = line.substr(0, splitLocation);
				std::string value = line.substr(splitLocation + 1);
				sections[selectedSection].AddDataValue(field, value);
			}
			// Section line
			else if (line[0] == '[') {
				std::string str = line.substr(1, line.find(']') - 1);
				AddSection(str);
				SelectSection(str);
			}
			else
				std::cout << "error on line " << lineNumber << std::endl;
		}
		return true;
	}

	void Config::RemoveWhiteSpaces(std::string& str) {
		int size = str.size();
		char *str2 = new char[size];
		int count = 0;

		for (int i = 0; i < size; i++) {
			if (!(str[i] == ' ' || str[i] == '\t'))
				str2[count++] = str[i];
		}
		str2[count] = '\0';
		str = str2;	// assign back to string..
	}
}