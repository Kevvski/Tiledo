#include "ResourceHelper.h"
#include <filesystem>
#include <QMessageBox>
#include <QDesktopWidget>

QString loadQss(const QString& fileName)
{
    QString fileContent{};
    QFile file(":/qss/" + fileName);

    if(file.open(QIODevice::ReadOnly))
        fileContent = file.readAll();

    file.close();
    return fileContent;
}


void setWindowInCenter(QWidget* widget, const QPoint& offset)
{
    QDesktopWidget desktop;
    QRect screen { desktop.screenGeometry() };
    QPoint newPos { (screen.width() - widget->width()) / 2, (screen.height() - widget->height()) / 2 };
    newPos.setX(newPos.x() + offset.x());
    newPos.setY(newPos.y() + offset.y());
    widget->setGeometry(newPos.x(), newPos.y(), widget->width(), widget->height());
}


QString ProjectProperties::projectName;
QString ProjectProperties::projectPath;
QString ProjectProperties::imagePath;
QPoint ProjectProperties::tileSize;
QPoint ProjectProperties::mapSize;
//QPixmap ProjectProperties::mainImage;
std::vector<QRect> ProjectProperties::tilesPoints;
std::vector<QPixmap> ProjectProperties::tiles;
TD::TDMap<GameTile> ProjectProperties::level;


void ProjectProperties::initialize(const QString &pName, const QString &iPath, const QPoint &tSize, const QPoint &mSize, bool loadProject)
{
    projectName = pName;
    projectPath = PROJECTS_DIR_PATH + "/" + projectName;
    imagePath = iPath;
    tileSize = tSize;
    mapSize = mSize;

    if(!loadProject)
    {
        std::filesystem::copy(imagePath.toStdString(), projectPath.toStdString());

        QStringList list = imagePath.split("/");

        imagePath = projectPath + "/" + list.last();
    }
}


void ProjectProperties::createProjectFile()
{
    level.setProperties(
        projectName.toStdString(),
        projectPath.toStdString(),
        imagePath.toStdString(),
        TD::TDVec2i{ tileSize.x(), tileSize.y() },
        TD::TDVec2i{ mapSize.x(), mapSize.y() });

    level.save();
}


void ProjectProperties::createTilesPoints()
{
    //mainImage = QPixmap{ imagePath };
    QPixmap mainImage{ imagePath };

    for(int i = 0; i < mainImage.size().height(); i += tileSize.y())
    {
        for(int j = 0; j < mainImage.size().width(); j += tileSize.x())
        {
            tilesPoints.push_back(QRect{ j, i, tileSize.x(), tileSize.y() });
        }
    }

    for(unsigned int i = 0; i < tilesPoints.size(); ++i)
    {
        const auto& tileRect = tilesPoints.at(i);
        level.addLegend(i, TD::TDVec2i{ tileRect.x(), tileRect.y() });
    }

    level.save();
}


void ProjectProperties::createTiles()
{
    QPixmap mainImage{ imagePath };

    for(const auto& rect : tilesPoints)
        tiles.push_back(mainImage.copy(rect));
}


void ProjectProperties::addTile(const GameTile &tile)
{
    level.addTile(tile);
}


void ProjectProperties::addLocation(const Location &location)
{
    level.addLocation(location.getStdName(), location.getTDPosition());
}


void ProjectProperties::clearMap()
{
    level.clear();
}


bool ProjectProperties::saveProject()
{
    if(level.save())
    {
        level.clear();
        return true;
    }

    return false;
}


bool ProjectProperties::loadProjectFile(const QString& fileName)
{
    if(!level.loadFromFile(fileName.toStdString()))
        return false;

    projectName = QString::fromStdString(level.getProperites().projectName);
    projectPath = QString::fromStdString(level.getProperites().projectPath);
    imagePath = QString::fromStdString(level.getProperites().imagePath);
    tileSize = QPoint(level.getProperites().tileSize.x,level.getProperites().tileSize.y);
    mapSize = QPoint(level.getProperites().mapSize.x,level.getProperites().mapSize.y);

    if(!level.getLegend().isEmpty())
    {
        for(unsigned int i = 0; i < level.getLegend().getSize(); ++i)
        {
            const auto& dataVec = level.getLegend().getRect(i);
            QRect rect{ dataVec.x, dataVec.y, level.getProperites().tileSize.x, level.getProperites().tileSize.y };
            tilesPoints.push_back(rect);
        }

        createTiles();
    }

    return true;
}


bool ProjectProperties::isLevelEmpty()
{
    return level.isEmpty();
}


bool ProjectProperties::levelHasLocations()
{
    return level.hasLocations();
}


const QString& ProjectProperties::getProjectName()
{
    return projectName;
}


const QString& ProjectProperties::getProjectPath()
{
    return projectPath;
}


const QString& ProjectProperties::getImagePath()
{
    return imagePath;
}


std::size_t ProjectProperties::getTilesCount()
{
    return tiles.size();
}


std::size_t ProjectProperties::getLevelTilesCount()
{
    return level.size();
}


std::size_t ProjectProperties::getLocationsCount()
{
    return level.locationsSize();
}


const QRect& ProjectProperties::getTextureRect(std::size_t index)
{
    return tilesPoints.at(index);
}


const QPixmap& ProjectProperties::getPixmap(std::size_t index)
{
    return tiles.at(index);
}


const QPoint ProjectProperties::getTileSize()
{
    QPoint point { level.getProperites().tileSize.x,  level.getProperites().tileSize.y };
    return point;
}


const QPoint ProjectProperties::getMapSize()
{
    QPoint point { level.getProperites().mapSize.x,  level.getProperites().mapSize.y };
    return point;
}


GameTile& ProjectProperties::getTile(size_t index)
{
    return level.getTile(index);
}


const Location ProjectProperties::getLocation(size_t index)
{
    Location location{ level.getLocation(index).name, level.getLocation(index).position };
    return location;
}
