#include "stdafx.h"
#include "TDTile.h"


TD::TDTile::TDTile()
{
}


TD::TDTile::~TDTile()
{
}


void TD::TDTile::setID(unsigned int value)
{
	id = value;
}


void TD::TDTile::setOnMapPosition(const TD::TDVec2i& position)
{
	onMapPosition = position;
}


const unsigned int TD::TDTile::getID() const
{
	return id;
}


const TD::TDVec2i& TD::TDTile::getOnMapPosition() const
{
	return onMapPosition;
}