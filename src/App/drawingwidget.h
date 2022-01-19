#ifndef DRAWINGWIDGET_H
#define DRAWINGWIDGET_H
#include <QWidget>
#include <QWheelEvent>
#include <vector>
#include "gametile.h"
#include "location.h"
#include "checksurface.h"

class DrawingWidget : public QWidget
{
    Q_OBJECT

public:
    DrawingWidget(QWidget* parent = nullptr);
    ~DrawingWidget();

    void initialize();
    void setToSave();

    unsigned int getDrawedTiles() const;
    unsigned int getTilesCount() const;
    float getScale() const;
    const GameTile& getTile(size_t index) const;

private:
    float scale;
    bool gridVisiblity;
    bool locationsVisiblity;
    bool mouseLeftPressed;
    bool mouseRightPressed;
    QPoint mousePosition;
    std::vector<GameTile> tiles;
    std::vector<Location> locations;
    CheckSurface checkSurface;

protected:
    virtual void paintEvent(QPaintEvent* e) override;
    virtual void wheelEvent(QWheelEvent *event) override;
    virtual void mousePressEvent(QMouseEvent *event) override;
    virtual void mouseReleaseEvent(QMouseEvent *event) override;
    virtual void mouseMoveEvent(QMouseEvent *event) override;

private:
    void drawTiles();
    void drawLocations();

public slots:
    void showGrid();
    void hideGrid();
    void showLocations();
    void hideLocations();
    void locationEdited(size_t index);
    void locationDeleted(size_t index);
    bool saveProject();

signals:
    void scaleChanged();
    void tileDrawed();
    void locationAdded(QString name);
    void locationEditedSuccess(int index, QString name);
};

#endif // DRAWINGWIDGET_H
