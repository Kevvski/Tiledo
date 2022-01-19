#include "stdafx.h"
#include "TDParser.h"
#include <iostream>
#include <fstream>

std::string TD::TDParser::data;

TD::TDParser::TDParser()
{
}


TD::TDParser::~TDParser()
{
}


bool TD::TDParser::loadFromFile(const std::string& fileName)
{
	std::fstream file;
	std::string line;

	file.open(fileName, std::ios::in);

	if (!file.is_open())
	{
		std::cerr << "Error: Load " + fileName + " failed.\n";
		file.close();
		return false;
	}

	while (std::getline(file, line))
	{
		data += line + "\n";
	}

	file.close();

	return true;
}


void TD::TDParser::getProperties(TD::TDProperties& properties)
{
	size_t startIndex{ data.find("Properties") };

	if (startIndex != std::string::npos)
	{
		startIndex += 10;
		const size_t LAST_INDEX{ data.find_first_of("}", startIndex) - 1 };
		std::vector<std::string> stringList;

		while (startIndex < LAST_INDEX)
		{
			size_t equalIndex{ data.find_first_of("=", startIndex) };
			size_t endLineIndex{ data.find_first_of("\n", equalIndex) };
			stringList.push_back(data.substr(equalIndex + 1, endLineIndex - equalIndex - 1));
			startIndex = endLineIndex;
		}

		if (!stringList.empty())
		{
			properties.projectName = stringList.at(0);
			properties.projectPath = stringList.at(1);
			properties.imagePath = stringList.at(2);
			properties.tileSize = TD::TDVec2i(stringList.at(3));
			properties.mapSize = TD::TDVec2i(stringList.at(4));
		}
	}
}


void TD::TDParser::getTileLegend(TD::TDLegend& legend)
{
	size_t startIndex{ data.find("Tile_Legend") };

	if (startIndex != std::string::npos)
	{
		startIndex += 11;
		const size_t LAST_INDEX{ data.find_first_of("}", startIndex) - 1};

		while (startIndex < LAST_INDEX)
		{
			size_t equalIndex{ data.find_first_of("=", startIndex) };
			size_t endLineIndex{ data.find_first_of("\n", equalIndex) };
			int id{ std::atoi(data.substr(startIndex + 1, equalIndex - startIndex - 1).c_str()) };
			TDVec2i vec{ data.substr(equalIndex + 1, endLineIndex - equalIndex - 1) };

			legend.addLegend(static_cast<unsigned int>(id), vec);

			startIndex = endLineIndex;
		}
	}
}


void TD::TDParser::getLocations(std::vector<TD::TDLocation>& locations)
{
	size_t startIndex{ data.find("Locations") };

	if (startIndex != std::string::npos)
	{
		startIndex += 9;
		const size_t LAST_INDEX{ data.find_first_of("}", startIndex) - 1 };

		while (startIndex < LAST_INDEX)
		{
			size_t equalIndex{ data.find_first_of("=", startIndex) };
			size_t endLineIndex{ data.find_first_of("\n", equalIndex) };
			std::string name{ data.substr(startIndex + 1, equalIndex - startIndex - 1) };
			TDVec2i vec{ data.substr(equalIndex + 1, endLineIndex - equalIndex - 1) };

			locations.push_back(TD::TDLocation{ name ,  vec });

			startIndex = endLineIndex;
		}
	}
}
