#include "mainappwg.h"
#include <QPainter>
#include "ResourceHelper.h"

MainAppWG::MainAppWG(QWidget *parent) : QWidget(parent)
{
    initialize();
    addToLayout();
    connectUI();
}


void MainAppWG::initialize()
{
    tilesTable = new TilesTableWidget(this);
    locationsDialog = new LocationsDialog(this);
    drawingWidget = new DrawingWidget(this);
}


void MainAppWG::addToLayout()
{
    QHBoxLayout* layout = new QHBoxLayout;
    layout->addWidget(drawingWidget);

    setLayout(layout);
}


void MainAppWG::connectUI()
{
    connect(tilesTable, &TilesTableWidget::showGrid, drawingWidget, &DrawingWidget::showGrid);
    connect(tilesTable, &TilesTableWidget::hideGrid, drawingWidget, &DrawingWidget::hideGrid);
    connect(tilesTable, &TilesTableWidget::showLocations, drawingWidget, &DrawingWidget::showLocations);
    connect(tilesTable, &TilesTableWidget::hideLocations, drawingWidget, &DrawingWidget::hideLocations);

    connect(locationsDialog, &LocationsDialog::addingLocation, tilesTable, &TilesTableWidget::releaseButtons);
    connect(locationsDialog, &LocationsDialog::editingLocation, drawingWidget, &DrawingWidget::locationEdited);
    connect(locationsDialog, &LocationsDialog::deletingLocation, drawingWidget, &DrawingWidget::locationDeleted);

    connect(drawingWidget, &DrawingWidget::locationAdded, locationsDialog, &LocationsDialog::locationAdded);
    connect(drawingWidget, &DrawingWidget::locationEditedSuccess, locationsDialog, &LocationsDialog::locationEdited);
}


void MainAppWG::createWidgets()
{
    tilesTable->addTilesToTable();
    tilesTable->show();

    locationsDialog->show();

    drawingWidget->initialize();
}


DrawingWidget* MainAppWG::getDrawingWidget() const
{
    return drawingWidget;
}




//------------------------------------------------SLOTS------------------------------------------------
bool MainAppWG::saveProject()
{
    return drawingWidget->saveProject();
}

