#ifndef PAINTERMANAGER_H
#define PAINTERMANAGER_H
#include <QPainter>

class PainterManager
{
public:
    PainterManager();
    ~PainterManager();

    static void setBrush(const QBrush& color);

    static void beginDraw(QPaintDevice* device);
    static void endDraw();

    static void translate(const QPoint& moveValue);
    static void translateOnce(const QPoint& moveValue);

    static void drawGrid(const QPoint& tileSize, const QPoint& mapSize, float scale = 1.0f);
    static void drawRect(const QRectF& rect, const QBrush& brush = QBrush{ Qt::white });
    static void drawRect(const QRectF& rect, const QPixmap& pixmap, const QRectF& sourceRect);
    static void drawEllipse(const QPoint& position, int diameter);

    static const QPoint& getDrawingPosition();

private:
    static QPainter painter;
    static QPoint startDrawingPosition;
    static bool isTranslated;
};

#endif // PAINTERMANAGER_H
