#pragma once

#ifndef TDMAP_H
#define TDMAP_H
#include <vector>
#include <iostream>
#include <fstream>
#include "TDParser.h"

namespace TD
{
	template<class T>
	class TDMap
	{
	private:
		TDProperties properties;
		TDLegend legend;
		std::vector<T> tiles;
		std::vector<TDLocation> locations;

	public:
		TDMap() {}
		virtual ~TDMap() {}

		void setProperties(const std::string& projectName, const std::string& projectPath, const std::string& imagePath, const TDVec2i& tileSize, const TDVec2i& mapSize) 
		{
			static_assert(std::is_base_of<TDTile, T>::value, "Error: A given type is not derivative from TDTile.");
			properties.projectName = projectName;
			properties.projectPath = projectPath;
			properties.projectFile = projectPath + "/" + projectName + ".tmf";
			properties.imagePath = imagePath;
			properties.tileSize = tileSize;
			properties.mapSize = mapSize;
		}

		void addLegend(unsigned int id, const TDVec2i& vec)
		{
			legend.addLegend(id, vec);
		}

		void addTile(const T& tile)
		{
			tiles.push_back(tile);
		}

		void addLocation(const TDLocation& location) 
		{
			locations.push_back(location);
		}

		void addLocation(const std::string& name, const TDVec2i& position)
		{
			locations.push_back(TDLocation{ name, position });
		}

		bool save()
		{
			if (!checkBuffers()) return false;
			if (!saveToFile()) return false;
			return true;
		}

		bool loadFromFile(const std::string& fileName)
		{
			if (!TDParser::loadFromFile(fileName))
				return false;

			properties.projectFile = fileName;

			TDParser::getProperties(properties);
			TDParser::getTileLegend(legend);
			TDParser::getTiles(tiles);
			TDParser::getLocations(locations);

			return true;
		}

		void draw()
		{
			if (!tiles.empty())
			{
				for (const auto& tile : tiles)
					tile.draw();
			}
		}

		void clear()
		{
			if (!tiles.empty())
				tiles.clear();

			if (!locations.empty())
				locations.clear();
		}

		const TDProperties& getProperites() const 
		{
			return properties;
		}

		const TDLegend& getLegend() const
		{
			return legend;
		}

		T& getTile(size_t index)
		{
			if (index >= 0 && index <= tiles.size() - 1)
				return tiles.at(index);
		}

		const TDLocation& getLocation(size_t index) {
			if (index >= 0 && index <= locations.size() - 1)
				return locations.at(index);
		}

		size_t size() const
		{
			return tiles.size();
		}

		size_t locationsSize() const
		{
			return locations.size();
		}

		bool isEmpty() const
		{
			return tiles.empty();
		}

		bool hasLocations() const
		{
			return !locations.empty();
		}

	private:
		bool checkBuffers() 
		{
			if (properties.projectFile.empty())
			{
				std::cerr << "Error: Before save map, please set project properties.\n";
				return false;
			}

			return true;
		}

		bool saveToFile() 
		{
			std::fstream file;
			file.open(properties.projectFile, std::ios::out);

			if (!file.is_open())
			{
				std::cerr << "Error: Can't open file: " + properties.projectFile << std::endl;
				file.close();
				return false;
			}

			file << "Properties\n{\n";
			file << "project_name=" + properties.projectName + "\n";
			file << "project_path=" + properties.projectPath + "\n";
			file << "image_path=" + properties.imagePath + "\n";
			file << "tile_size=" + properties.tileSize.toString() + "\n";
			file << "map_size=" + properties.mapSize.toString() + "\n}\n";

			if (!legend.isEmpty())
				file << legend.toString();

			if (!tiles.empty())
			{
				file << "Tiles_Positions\n{\n";

				for (const auto& tile : tiles)
					file << std::to_string(tile.getID()) + "-" + tile.getOnMapPosition().toString() + "\n";

				file << "}\n";
			}

			if (!locations.empty())
			{
				file << "Locations\n{\n";

				for (const auto& location : locations)
					file << location.name << "=" << location.position.toString() + "\n";

				file << "}\n";
			}

			/*
			file << "Collisions\n{\n";
			file << "\n}";
			*/

			file.close();
			return true;
		}
	};
}
#endif // !TDMAP_H
