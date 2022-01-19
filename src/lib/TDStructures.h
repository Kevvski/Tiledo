#pragma once

/*#ifdef TILEDO_EXPORTS
#define TILEDO_API __declspec(dllexport)
#else
#define TILEDO_API __declspec(dllimport)
#endif*/

#ifndef TDSTRUCTURES_H
#define TDSTRUCTURES_H
#include <string>
#include <map>

namespace TD
{
	struct TDVec2i
	{
		TDVec2i() : x{ 0 }, y{ 0 } {};
		TDVec2i(int _x, int _y) : x{ _x }, y{ _y } {};
		TDVec2i(const std::string& text)
		{
			size_t separator{ text.find_first_of(",") };
			x = std::atoi(text.substr(0, separator).c_str());
			y = std::atoi(text.substr(separator + 1, text.size() - separator - 1).c_str());
		}

		int x, y;
		std::string toString() const
		{
			return std::to_string(x) + "," + std::to_string(y);
		}
	};

	struct TDRectI
	{
		TDRectI() : x{ 0 }, y{ 0 }, width{ 0 }, height{ 0 } {};
		TDRectI(int _x, int _y, int _width, int _height) : x{ _x }, y{ _y }, width{ _width }, height{ _height } {};
		TDRectI(const std::string& text)
		{
			size_t firstSeparator{ text.find(",") };
			size_t secondSeparator{ text.find(",", firstSeparator) };
			size_t thirdSeparator{ text.find(",", secondSeparator) };
			
			x = std::atoi(text.substr(0, firstSeparator - 1).c_str());
			y = std::atoi(text.substr(firstSeparator + 1, secondSeparator - firstSeparator - 1).c_str());
			width = std::atoi(text.substr(secondSeparator + 1, thirdSeparator - secondSeparator - firstSeparator - 1).c_str());
			height = std::atoi(text.substr(thirdSeparator + 1, text.size() - thirdSeparator - secondSeparator - firstSeparator - 1).c_str());
		}

		int x, y, width, height;
		std::string toString() const
		{
			return std::to_string(x) + "," + std::to_string(y) + "," + std::to_string(width) + "," + std::to_string(height);
		}
	};

	struct TDProperties
	{
		std::string projectName;
		std::string projectPath;
		std::string projectFile;
		std::string imagePath;
		TDVec2i tileSize;
		TDVec2i mapSize;
	};

	struct TDLegend
	{
		std::map<unsigned int, TDVec2i> data;

		void addLegend(unsigned int id, const TDVec2i& rect)
		{
			data.insert(std::pair<unsigned int, TDVec2i>(id, rect));
		}

		std::string toString() const
		{
			std::string localData{ "Tile_Legend\n{\n" };
			if (!data.empty())
			{
				for (const auto& d : data)
					localData += std::to_string(d.first) + "=" + d.second.toString() + "\n";
			}
			localData += "}\n";
			return localData;
		}

		bool isEmpty() const
		{
			return data.empty();
		}

		size_t getSize() const
		{
			return data.size();
		}

		const TDVec2i& getRect(unsigned int id) const
		{
			if (!data.empty())
				return data.at(id);
		}
	};

	struct TDLocation
	{
		std::string name;
		TDVec2i position;
	};
}

#endif // !TDSTRUCTURES_H
