#ifndef INDEXERINTERFACE_H
#define INDEXERINTERFACE_H


class IndexerInterface
{
public:
    IndexerInterface();

    enum AVAIABLE_STATE : int
    {
        NORMAL = -1,
        DRAW = 0,
        DELETE = -2,
        SET_LOCATION = -3
    };

    static void setIndex(int value);

    static int getIndex();
    static bool isAvaiable();
    static bool isAvaiableToDraw();
    static bool isAvaiableToDelete();
    static bool isAvaibleToSetLocation();

private:
    static int currentTileIndex;
};

#endif // INDEXERINTERFACE_H
