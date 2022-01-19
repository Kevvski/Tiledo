#include "indexerinterface.h"

int IndexerInterface::currentTileIndex { -1 };

IndexerInterface::IndexerInterface()
{

}


void IndexerInterface::setIndex(int value)
{
    currentTileIndex = value;
}


int IndexerInterface::getIndex()
{
    return currentTileIndex;
}


bool IndexerInterface::isAvaiable()
{
    return currentTileIndex == IndexerInterface::NORMAL;
}


bool IndexerInterface::isAvaiableToDraw()
{
    return currentTileIndex >= IndexerInterface::DRAW;
}


bool IndexerInterface::isAvaiableToDelete()
{
    return currentTileIndex == IndexerInterface::DELETE;
}


bool IndexerInterface::isAvaibleToSetLocation()
{
    return  currentTileIndex == IndexerInterface::SET_LOCATION;
}
