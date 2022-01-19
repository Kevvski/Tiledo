#include "checksurface.h"
#include "paintermanager.h"

CheckSurface::CheckSurface() : rect{0.0f, 0.0f, 0.0f, 0.0f}, isDrawing{ false }
{
}


void CheckSurface::setStartPosition(const QPoint &position)
{
    rect.setX(static_cast<float>(position.x()));
    rect.setY(static_cast<float>(position.y()));
}


void CheckSurface::setEndPosition(const QPoint &position)
{
    isDrawing = true;
    rect.setWidth(static_cast<float>(position.x()) - rect.x());
    rect.setHeight(static_cast<float>(position.y()) - rect.y());
}


void CheckSurface::setColor(const QBrush &brush)
{
    color = brush;
}


void CheckSurface::draw()
{
    if(isDrawing)
        PainterManager::drawRect(rect, color);
}


void CheckSurface::clear()
{
    isDrawing = false;
    rect = QRectF{0.0f, 0.0f, 0.0f, 0.0f};
    color = Qt::transparent;
}


bool CheckSurface::contains(const QRectF &rectValue) const
{
    return rect.intersects(rectValue);
}
