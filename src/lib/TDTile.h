#pragma once

#ifdef TILEDO_EXPORTS
#define TILEDO_API __declspec(dllexport)
#else
#define TILEDO_API __declspec(dllimport)
#endif

#ifndef TDTILE_H
#define TDTILE_H
#include "TDStructures.h"

namespace TD
{
	class TILEDO_API TDTile
	{
	public:
		TDTile();
		virtual ~TDTile();

		void setID(unsigned int value);
		void setOnMapPosition(const TDVec2i& position);
		virtual void setPosition() = 0; //For drawing objects
		virtual void setTextureRectangle(const TDRectI& rect) = 0;
		virtual void draw() = 0;

		const unsigned int getID() const;
		const TDVec2i& getOnMapPosition() const;

	private:
		unsigned int id;
		TDVec2i onMapPosition;
	};
}

#endif // !TDTILE_H

