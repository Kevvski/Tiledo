#ifndef LOCATION_H
#define LOCATION_H
#include <QBrush>
#include "TDStructures.h"
#include "paintermanager.h"

class Location
{
public:
    Location();
    Location(const QString& name, const QPoint& position);
    Location(const std::string& name, const TD::TDVec2i& position);

    void setName(const QString& name);
    void setPosition(const QPoint& position);
    void setPositionDifference(const QPoint& value);
    void setColor(const QBrush& color);
    void setDiameter(int diameter);

    void draw();
    void clear();

    const QString& getName() const;
    const QPoint& getPosition() const;
    const QPoint& getPositionDifference() const;
    const QColor& getColor() const;
    const std::string getStdName() const;
    const TD::TDVec2i getTDPosition() const;
    int getDiameter() const;

private:
    bool isDrawing;
    int diameter;
    QBrush color;
    QString name;
    QPoint position;
    QPoint differencePosition;
};

#endif // LOCATION_H
