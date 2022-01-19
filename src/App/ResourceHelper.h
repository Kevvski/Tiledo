#ifndef RESOURCEHELPER_H
#define RESOURCEHELPER_H
#include <QString>
#include <QFile>
#include <QDir>
#include <QPoint>
#include <QRect>
#include <QPixmap>
#include <vector>
#include <QDebug>
#include "TDMap.h"
#include "gametile.h"
#include "location.h"

QString loadQss(const QString& fileName);
void setWindowInCenter(QWidget* widget, const QPoint& offset = {0, 0});

static const QString PROJECTS_DIR_PATH { QDir::homePath() + "/TiledProjects" };
static const QString CLICKED_BUTTON_STYLE { "background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 #78ff9c, stop: 1 green);" };

class ProjectProperties
{

public:
    static void initialize(const QString& pName, const QString& iPath, const QPoint& tSize, const QPoint& mSize, bool loadProject = false);
    static void createProjectFile();
    static void createTilesPoints();
    static void createTiles();
    static void addTile(const GameTile& tile);
    static void addLocation(const Location& location);
    static void clearMap();
    static bool saveProject();
    static bool loadProjectFile(const QString& fileName);
    static bool isLevelEmpty();
    static bool levelHasLocations();

    static const QString& getProjectName();
    static const QString& getProjectPath();
    static const QString& getImagePath();
    static std::size_t getTilesCount();
    static std::size_t getLevelTilesCount();
    static std::size_t getLocationsCount();
    static const QRect& getTextureRect(std::size_t index);
    static const QPixmap& getPixmap(std::size_t index);
    static const QPoint getTileSize();
    static const QPoint getMapSize();
    static GameTile& getTile(size_t index);
    static const Location getLocation(size_t index);

private:
    static QString projectName;
    static QString projectPath;
    static QString imagePath;
    static QPoint tileSize;
    static QPoint mapSize;
    //static QPixmap mainImage;
    static std::vector<QRect> tilesPoints;
    static std::vector<QPixmap> tiles;
    static TD::TDMap<GameTile> level;
};

#endif // RESOURCEHELPER_H
