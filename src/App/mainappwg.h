#ifndef MAINAPPWG_H
#define MAINAPPWG_H

#include <QWidget>
#include <QTextEdit>
#include "tilestablewidget.h"
#include "drawingwidget.h"
#include "locationsdialog.h"

class MainAppWG : public QWidget
{
    Q_OBJECT

public:
    explicit MainAppWG(QWidget *parent = nullptr);

    void createWidgets();

    DrawingWidget* getDrawingWidget() const;

private:
    TilesTableWidget* tilesTable;
    LocationsDialog* locationsDialog;
    DrawingWidget* drawingWidget;

private:
    void initialize();
    void addToLayout();
    void connectUI();

public slots:
    bool saveProject();
};

#endif // MAINAPPWG_H
