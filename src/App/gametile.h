#ifndef GAMETILE_H
#define GAMETILE_H
#include <QRectF>
#include <QPixmap>
#include <QBrush>
#include "TDTile.h"

class GameTile : public TD::TDTile
{
public:
    GameTile();
    virtual ~GameTile();

    virtual void setPosition() override;
    virtual void setTextureRectangle(const TD::TDRectI &rect) override;
    virtual void draw() override;

    void setRect(const QRectF& rect);
    void setTexture(const QRect& rect);
    void setPixmap(const QPixmap& pix);
    void setBrush(const QBrush& brush);
    void fill(const QColor &color = Qt::white);
    void clear();

    const QRectF& getRect() const;
    bool contains(const QPoint& point) const;
    bool isDrawed() const;

private:
    QRectF rectShape;
    QRectF textureRect;
    QPixmap pixmap;
    QBrush color;
    bool isPixmap;
};

#endif // GAMETILE_H
