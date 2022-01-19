#ifndef CHECKSURFACE_H
#define CHECKSURFACE_H

#include <QRectF>
#include <QBrush>

class CheckSurface
{
public:
    CheckSurface();

    void setStartPosition(const QPoint& position);
    void setEndPosition(const QPoint& position);
    void setColor(const QBrush& brush);

    void draw();
    void clear();

    bool contains(const QRectF& rectValue) const;

private:
    QRectF rect;
    QBrush color;
    bool isDrawing;
};

#endif // CHECKSURFACE_H
