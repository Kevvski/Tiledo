#pragma once

#ifdef TILEDO_EXPORTS
#define TILEDO_API __declspec(dllexport)
#else
#define TILEDO_API __declspec(dllimport)
#endif

#ifndef TDPARSER_H
#define TDPARSER_H
#include <string>
#include <vector>
#include "TDStructures.h"
#include "TDTile.h"

namespace TD
{
	class TILEDO_API TDParser
	{
	public:
		TDParser();
		~TDParser();

		static bool loadFromFile(const std::string& fileName);
		static void getProperties(TDProperties& properties);
		static void getTileLegend(TDLegend& legend);
		static void getLocations(std::vector<TDLocation>& locations);

		template<typename T>
		static void getTiles(std::vector<T>& tiles)
		{
			size_t startIndex{ data.find("Tiles_Positions") };

			if (startIndex != std::string::npos)
			{
				startIndex += 15;
				const size_t LAST_INDEX{ data.find_first_of("}", startIndex) - 1 };
				bool firstRound{ true };

				while (startIndex < LAST_INDEX)
				{
					size_t separatorIndex{ data.find_first_of("-", startIndex) };
					size_t endLineIndex{ data.find_first_of("\n", separatorIndex) };
					int id{ std::atoi(data.substr(startIndex + 1, separatorIndex - startIndex - 1).c_str()) };
					TDVec2i position{ data.substr(separatorIndex + 1, endLineIndex - separatorIndex - 1) };

					T tile;
					tile.setID(static_cast<unsigned int>(id));
					tile.setOnMapPosition(position);

					tiles.push_back(tile);

					startIndex = endLineIndex;
				}
			}
		}

	private:
		static std::string data;
	};
}

#endif // !TDPARSER_H

