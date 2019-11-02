#pragma once

#include <iostream>
#include <string>
#include <fstream>
#include <map>

namespace config {
	class Config;
	class Section
	{
	public:
		Section() {}
		~Section() {}
		void AddDataValue(std::string field, std::string value) { this->dataValues[field] = value; }
		std::string GetFieldValue(std::string field) {
			try {
				return dataValues[field];
			}
			catch (std::out_of_range e) {
				return std::string("");
			}
		}
		friend class Config;
	private:
		std::map<std::string, std::string> dataValues;
	};


	class Config
	{
	public:
		Config() {}
		~Config() {}
		void clear() { sections.clear(); selectedSection = ""; }
		bool SelectSection(std::string sectionName);
		std::string GetFieldValue(std::string field) {
			try {
				return sections[selectedSection].GetFieldValue(field);
			}
			catch (std::out_of_range e) {
				return std::string("");
			}
		}
		void AddSection(std::string name) { sections[name] = Section(); }
		void AddDataValue(std::string field, std::string value) { sections[selectedSection].AddDataValue(field, value); }
		bool LoadFile(const char* fileName);
		bool SaveFile(const char* fileName);

	protected:
		void RemoveWhiteSpaces(std::string& str);
	private:
		std::string selectedSection;
		std::map<std::string, Section> sections;
	};
}