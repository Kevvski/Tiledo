#include "location.h"

Location::Location() : isDrawing{ false }, diameter{ 20 }, name{}, position{}
{
}


Location::Location(const QString& name, const QPoint& position) : isDrawing{ true }, diameter{ 20 }
{
    this->name = name;
    this->position.setX(position.x());
    this->position.setY(position.y());
    this->color = QColor{ Qt::green };
}


Location::Location(const std::string& name, const TD::TDVec2i& position) : isDrawing{ true }, diameter{ 20 }
{
    this->name = QString::fromStdString(name);
    this->position.setX(position.x);
    this->position.setY(position.y);
    this->color = QColor{ Qt::green };
}


void Location::setName(const QString &name)
{
    isDrawing = true;
    this->name = name;
}


void Location::setPosition(const QPoint &position)
{
    this->position = position;
}


void Location::setPositionDifference(const QPoint &value)
{
    this->differencePosition = value;
}


void Location::setColor(const QBrush &color)
{
    this->color = color;
}


void Location::setDiameter(int diameter)
{
    this->diameter = diameter;
}


void Location::draw()
{
    if(isDrawing)
    {
        PainterManager::setBrush(color);
        PainterManager::drawEllipse(position, diameter);
        PainterManager::setBrush(Qt::transparent);
    }
}


void Location::clear()
{
    isDrawing = false;
    position = QPoint{ 0, 0 };
}


const QString& Location::getName() const
{
    return name;
}


const QPoint& Location::getPosition() const
{
    return position;
}


const QPoint& Location::getPositionDifference() const
{
    return differencePosition;
}


const QColor& Location::getColor() const
{
    return color.color();
}


const std::string Location::getStdName() const
{
    return name.toStdString();
}


const TD::TDVec2i Location::getTDPosition() const
{
    return TD::TDVec2i{ position.x(), position.y() };
}


int Location::getDiameter() const
{
    return diameter;
}
