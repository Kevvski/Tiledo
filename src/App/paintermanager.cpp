#include "paintermanager.h"

QPainter PainterManager::painter;
QPoint PainterManager::startDrawingPosition{ 0, 0 };
bool PainterManager::isTranslated{ false };

PainterManager::PainterManager()
{
}


PainterManager::~PainterManager()
{

}


void PainterManager::setBrush(const QBrush &color)
{
    if(painter.device() != nullptr)
        painter.setBrush(color);
}


void PainterManager::beginDraw(QPaintDevice *device)
{
    painter.begin(device);
    painter.setRenderHint(QPainter::Antialiasing);
}


void PainterManager::endDraw()
{
    painter.end();
}


void PainterManager::translate(const QPoint &moveValue)
{
    if(painter.device() != nullptr)
    {
        startDrawingPosition.setX(moveValue.x());
        startDrawingPosition.setY(moveValue.y());
    }
}


void PainterManager::translateOnce(const QPoint &moveValue)
{
    if(!isTranslated && painter.device() != nullptr)
    {
        isTranslated = true;
        startDrawingPosition.setX(moveValue.x());
        startDrawingPosition.setY(moveValue.y());
    }
}


void PainterManager::drawGrid(const QPoint& tileSize, const QPoint& mapSize, float scale)
{
    if(painter.device() != nullptr)
    {
        const QPoint MAP_SIZE_RESULT { mapSize.x() * tileSize.x(), mapSize.y() * tileSize.y()};

        for(float i = 0; i <= MAP_SIZE_RESULT.x(); i += tileSize.x())
        {
            painter.drawLine(
                (startDrawingPosition.x() + i) * scale,
                startDrawingPosition.y() * scale,
                (startDrawingPosition.x() + i) * scale,
                (startDrawingPosition.y() + MAP_SIZE_RESULT.y()) * scale);
        }

        for(float i = 0; i <= MAP_SIZE_RESULT.y(); i += tileSize.y())
        {
            painter.drawLine(
                startDrawingPosition.x() * scale,
                (startDrawingPosition.y() + i) * scale,
                (startDrawingPosition.x() + MAP_SIZE_RESULT.x()) * scale,
                (startDrawingPosition.y() + i) * scale);
        }
    }
}


void PainterManager::drawRect(const QRectF &rect, const QBrush& brush)
{
    if(painter.device() != nullptr)
        painter.fillRect(rect, brush);
}


void PainterManager::drawRect(const QRectF &rect, const QPixmap& pixmap, const QRectF& sourceRect)
{
    if(painter.device() != nullptr)
        painter.drawPixmap(rect, pixmap, sourceRect);
}


void PainterManager::drawEllipse(const QPoint &position, int diameter)
{
    if(painter.device() != nullptr)
        painter.drawEllipse(position.x(), position.y(), diameter / 2, diameter / 2);
}


const QPoint& PainterManager::getDrawingPosition()
{
    return startDrawingPosition;
}
