#include "drawingwidget.h"
#include "ResourceHelper.h"
#include "paintermanager.h"
#include "indexerinterface.h"
#include "createlocationdialog.h"
#include <cmath>
#include <QMessageBox>

DrawingWidget::DrawingWidget(QWidget* parent) : QWidget(parent), scale{ 1.0f }, gridVisiblity{ true }, locationsVisiblity{ true }, mouseLeftPressed{ false },
      mouseRightPressed{ false }
{
}


DrawingWidget::~DrawingWidget()
{
}


void DrawingWidget::initialize()
{
    this->setMouseTracking(true);
    const auto TILE_SIZE { ProjectProperties::getTileSize() };
    const auto MAP_SIZE { ProjectProperties::getMapSize() };

    for(float i = 0; i < MAP_SIZE.x() * TILE_SIZE.x(); i += TILE_SIZE.x())
    {
        for(float j = 0; j < MAP_SIZE.y() * TILE_SIZE.y(); j += TILE_SIZE.y())
        {
            GameTile tile;
            tile.setRect(QRectF{ j, i, static_cast<float>(TILE_SIZE.x()), static_cast<float>(TILE_SIZE.y()) });
            tiles.push_back(tile);
        }
    }

    //TODO: Solve a problem with first tile with 0 index and last tile without index
    if(!ProjectProperties::isLevelEmpty())
    {
        for(size_t i = 0; i < ProjectProperties::getLevelTilesCount(); ++i)
        {
            const auto& projectTile = ProjectProperties::getTile(i);
            for(auto& tile : tiles)
            {
                if(tile.getOnMapPosition().x == projectTile.getOnMapPosition().x && tile.getOnMapPosition().y == projectTile.getOnMapPosition().y)
                {
                    tile.setID(projectTile.getID());
                    tile.setPixmap(ProjectProperties::getPixmap(projectTile.getID()));
                }
            }
        }
    }

    //TODO: Save diameter and position color to file and put here to locations
    if(ProjectProperties::levelHasLocations())
    {
        for(size_t i = 0; i < ProjectProperties::getLocationsCount(); ++i)
            locations.push_back(ProjectProperties::getLocation(i));

        for(auto& location : locations)
            location.setPositionDifference(location.getPosition() - PainterManager::getDrawingPosition());
    }

    ProjectProperties::clearMap();
}


void DrawingWidget::setToSave()
{
    PainterManager::translate(QPoint{ 0, 0 });
    scale = 1.0f;
    emit scaleChanged();
    repaint();
}


unsigned int DrawingWidget::getDrawedTiles() const
{
    return std::count_if(tiles.begin(), tiles.end(), [](const GameTile& tile){
        if(tile.isDrawed())
            return true;
        else
            return false;
    });
}


unsigned int DrawingWidget::getTilesCount() const
{
    return tiles.size();
}


float DrawingWidget::getScale() const
{
    return scale;
}


const GameTile& DrawingWidget::getTile(size_t index) const
{
    if(index >= 0 && index <= tiles.size() - 1)
        return tiles.at(index);
}


void DrawingWidget::paintEvent(QPaintEvent *e)
{
    const auto TILE_SIZE { ProjectProperties::getTileSize() };
    const auto MAP_SIZE { ProjectProperties::getMapSize() };
    QPoint translatePoint { (width() / 2) - (MAP_SIZE.x() * TILE_SIZE.x() / 2), (height() / 2) - (MAP_SIZE.y() * TILE_SIZE.y() / 2) };

    PainterManager::beginDraw(this);
    PainterManager::translateOnce(translatePoint);

    drawTiles();

    if(locationsVisiblity)
        drawLocations();

    if(gridVisiblity)
        PainterManager::drawGrid(TILE_SIZE, MAP_SIZE, scale);

    checkSurface.draw();

    PainterManager::endDraw();
}


void DrawingWidget::wheelEvent(QWheelEvent *event)
{
    const auto RESULT = event->angleDelta().y();

    if(RESULT > 0 && scale < 4)
        scale += 0.2f;
    else if(RESULT < 0 && scale > 1)
        scale -= 0.2f;

    update();

    event->accept();
    emit scaleChanged();
}


void DrawingWidget::mousePressEvent(QMouseEvent *event)
{
    if(event->buttons() == Qt::LeftButton)
    {
        mouseLeftPressed = true;
        mouseRightPressed = false;
    }
    else if(event->buttons() == Qt::RightButton)
    {
        mouseRightPressed = true;
        mouseLeftPressed = false;
    }

    if(IndexerInterface::isAvaiable() && mouseLeftPressed)
    {
        this->setCursor(Qt::CursorShape::SizeAllCursor);
        mousePosition = event->pos() - PainterManager::getDrawingPosition();
    }
    else if(IndexerInterface::isAvaiableToDraw() && mouseRightPressed)
    {
        checkSurface.setStartPosition(event->pos());
        checkSurface.setColor(QColor{120, 168, 245, 100});
    }
    else if(IndexerInterface::isAvaiableToDelete() && mouseRightPressed)
    {
        checkSurface.setStartPosition(event->pos());
        checkSurface.setColor(QColor{255, 0, 0, 100});
    }
    else if(IndexerInterface::isAvaibleToSetLocation())
    {
        for(const auto& tile : tiles)
        {
            if(tile.contains(event->pos()) && mouseLeftPressed)
            {
               CreateLocationDialog dialog(false, this);
               dialog.setLocationPosition(QPoint{ tile.getOnMapPosition().x, tile.getOnMapPosition().y });

               if(dialog.exec())
               {
                   QPoint position {
                       dialog.getLocationPosition().x() + static_cast<int>((tile.getRect().width() / 2)) - (dialog.getDiameter() / 4),
                       dialog.getLocationPosition().y() + static_cast<int>((tile.getRect().height() / 2)) - (dialog.getDiameter() / 4)
                   };

                   Location location;
                   location.setPosition(position);
                   location.setPositionDifference(location.getPosition() - PainterManager::getDrawingPosition());
                   location.setName(dialog.getLocationName());
                   location.setDiameter(dialog.getDiameter());
                   location.setColor(dialog.getColor());

                   locations.push_back(location);

                   IndexerInterface::setIndex(IndexerInterface::NORMAL);
                   mouseLeftPressed = false;

                   emit locationAdded(dialog.getLocationName());
                   update();
               }
            }
        }
    }
}


void DrawingWidget::mouseReleaseEvent(QMouseEvent *event)
{
    mouseLeftPressed = false;
    mouseRightPressed = false;

    if(IndexerInterface::isAvaiable())
        this->setCursor(Qt::CursorShape::ArrowCursor);
    else if(IndexerInterface::isAvaiableToDraw() && !mouseRightPressed)
    {
        for(auto& tile : tiles)
        {
            if(checkSurface.contains(tile.getRect()))
            {
                tile.setID(IndexerInterface::getIndex());
                tile.setPixmap(ProjectProperties::getPixmap(IndexerInterface::getIndex()));
            }
        }

        checkSurface.clear();
        emit tileDrawed();
    }
    else if(IndexerInterface::isAvaiableToDelete() && !mouseRightPressed)
    {
        for(auto& tile : tiles)
        {
            if(checkSurface.contains(tile.getRect()))
                tile.clear();
        }

        checkSurface.clear();
        emit tileDrawed();
    }
}


void DrawingWidget::mouseMoveEvent(QMouseEvent *event)
{
    if(IndexerInterface::isAvaiable() && mouseLeftPressed)
    {
        PainterManager::translate(event->pos() - mousePosition);
    }
    else if(IndexerInterface::isAvaiableToDraw())
    {
        for(auto& tile : tiles)
        {
            if(tile.contains(event->pos()))
            {
                tile.setBrush(QBrush{ QColor{150, 250, 250} });

                if(mouseLeftPressed)
                {
                    tile.setID(IndexerInterface::getIndex());
                    tile.setPixmap(ProjectProperties::getPixmap(IndexerInterface::getIndex()));
                    emit tileDrawed();
                }
            }
            else
                tile.setBrush(QBrush{ Qt::white });
        }

        if(mouseRightPressed)
            checkSurface.setEndPosition(event->pos());
    }
    else if(IndexerInterface::isAvaiableToDelete())
    {
        for(auto& tile : tiles)
        {
            if(tile.contains(event->pos()))
            {
                if(mouseLeftPressed)
                {
                    tile.clear();
                    emit tileDrawed();
                }
            }
        }

        if(mouseRightPressed)
            checkSurface.setEndPosition(event->pos());
    }

    update();
}




//------------------------------------------------PRIVATE FUNCTIONS------------------------------------------------
void DrawingWidget::drawTiles()
{
    if(!tiles.empty())
    {
        const auto TILE_SIZE { ProjectProperties::getTileSize() };
        const auto MAP_SIZE { ProjectProperties::getMapSize() };

        QPoint newTilesPosition { PainterManager::getDrawingPosition() };
        const auto mapEndX { MAP_SIZE.x() * TILE_SIZE.x() + PainterManager::getDrawingPosition().x() };

        for(auto& tile : tiles)
        {
            if(newTilesPosition.x() >= mapEndX)
            {
                newTilesPosition.setY(newTilesPosition.y() + TILE_SIZE.y());
                newTilesPosition.setX(PainterManager::getDrawingPosition().x());
            }

            tile.setRect(QRectF{
                static_cast<float>(newTilesPosition.x()) * scale,
                static_cast<float>(newTilesPosition.y()) * scale,
                static_cast<float>(TILE_SIZE.x()) * scale,
                static_cast<float>(TILE_SIZE.y()) * scale });

            newTilesPosition.setX(newTilesPosition.x() + TILE_SIZE.x());

            tile.draw();
        }
    }
}


void DrawingWidget::drawLocations()
{
    if(!locations.empty())
    {
        for(auto& location : locations)
        {
            QPoint newPosition { PainterManager::getDrawingPosition() + location.getPositionDifference() };
            location.setPosition(newPosition * scale);
            location.draw();
        }
    }
}




//------------------------------------------------SLOTS------------------------------------------------
void DrawingWidget::showGrid()
{
    gridVisiblity = true;
    update();
}


void DrawingWidget::hideGrid()
{
    gridVisiblity = false;
    update();
}


void DrawingWidget::showLocations()
{
    locationsVisiblity = true;
    update();
}


void DrawingWidget::hideLocations()
{
    locationsVisiblity = false;
    update();
}

void DrawingWidget::locationEdited(size_t index)
{
    auto& location = locations.at(index);

    //TODO: Create one method with Location argument and emit location name
    CreateLocationDialog dialog(true, this);
    dialog.setLocationPosition(location.getPosition());
    dialog.setColor(location.getColor());
    dialog.setLocationName(location.getName());
    dialog.setDiameter(location.getDiameter());

    if(dialog.exec())
    {
        location.setName(dialog.getLocationName());
        location.setPosition(dialog.getLocationPosition());
        location.setPositionDifference(location.getPosition() - PainterManager::getDrawingPosition());
        location.setName(dialog.getLocationName());
        location.setDiameter(dialog.getDiameter());
        location.setColor(dialog.getColor());

        emit locationEditedSuccess(index, location.getName());
        update();
    }
}


void DrawingWidget::locationDeleted(size_t index)
{
    locations.erase(locations.begin() + index);
    update();
}


bool DrawingWidget::saveProject()
{
    setToSave();

    for(const auto& tile : tiles)
    {
        if(tile.isDrawed())
            ProjectProperties::addTile(tile);
    }

    if(!locations.empty())
    {
        for(const auto& location : locations)
            ProjectProperties::addLocation(location);
    }

    if(!ProjectProperties::saveProject())
    {
        QMessageBox::warning(this, "Project save failed!", "Save attempt failed.");
        return false;
    }

    QMessageBox::information(this, "Project saved!", "Project save successfully completed.");
    return true;
}
