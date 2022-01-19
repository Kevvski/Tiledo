#include "gametile.h"
#include "paintermanager.h"
#include <QDebug>
#include <QBitmap>

GameTile::GameTile() : rectShape{0.0f, 0.0f, 0.0f, 0.0f}, color{ Qt::white }, isPixmap{ false }
{
}


GameTile::~GameTile()
{
}


void GameTile::setPosition()
{
}


void GameTile::setTextureRectangle(const TD::TDRectI &rect)
{
}


void GameTile::draw()
{
    if(!isPixmap)
        PainterManager::drawRect(rectShape, color);
    else
        PainterManager::drawRect(rectShape, pixmap, textureRect);
}


void GameTile::setTexture(const QRect &rect)
{
    textureRect = rect;
}


void GameTile::setRect(const QRectF &position)
{
    setOnMapPosition(TD::TDVec2i{ static_cast<int>(position.x()), static_cast<int>(position.y()) });
    rectShape = position;
}


void GameTile::setPixmap(const QPixmap &pix)
{
    isPixmap = true;
    pixmap = pix;
}


void GameTile::setBrush(const QBrush &brush)
{
    color = brush;
}


void GameTile::fill(const QColor &color)
{
    if(isPixmap)
    {
        pixmap.fill(color);
    }
}


void GameTile::clear()
{
    if(isPixmap)
    {
        pixmap.detach();
        isPixmap = false;
    }
}


const QRectF& GameTile::getRect() const
{
    return rectShape;
}


bool GameTile::contains(const QPoint &point) const
{
    return rectShape.contains(point);
}


bool GameTile::isDrawed() const
{
    return isPixmap;
}
