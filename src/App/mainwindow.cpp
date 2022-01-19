#include "mainwindow.h"
#include <QDesktopWidget>
#include <QStatusBar>
#include <QMenuBar>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
    initialize();
    connectUI();
}


MainWindow::~MainWindow()
{
}


void MainWindow::initialize()
{
    resize(800, 600);
    setWindowTitle("TileDo");
    setStyleSheet("background-color: qlineargradient(x1: 0, y1: 0, x2: 1, y2: 1, stop: 0 #4fff7e, stop: 1 #40fcff);");

    QDir dir;
    QString path{ PROJECTS_DIR_PATH };

    if(!dir.exists(path))
        dir.mkpath(path);

    mainMenuWidget = new MainMenuWG(this);
    mainAppWidget = new MainAppWG;
    fileMenu= new QMenu;
    tilesCountLabel = new QLabel;
    scaleLabel = new QLabel;

    fileMenu->setTitle("File");
    fileMenu->addAction("Save", mainAppWidget, &MainAppWG::saveProject);
    fileMenu->addAction("Exit", this, &MainWindow::closeApp);

    setCentralWidget(mainMenuWidget);
}


void MainWindow::connectUI()
{
    connect(mainMenuWidget, &MainMenuWG::projectCreated, this, &MainWindow::changeWidget);
    connect(mainAppWidget->getDrawingWidget(), &DrawingWidget::tileDrawed, this, &MainWindow::changeDrawedTilesCount);
    connect(mainAppWidget->getDrawingWidget(), &DrawingWidget::scaleChanged, this, &MainWindow::changeScale);
}


void MainWindow::closeEvent(QCloseEvent *event)
{
    //TODO: create a question about save project before close app
    event->accept();
}




//------------------------------------------------SLOTS------------------------------------------------
void MainWindow::changeWidget()
{
    resize(1280, 720);
    setWindowTitle("TileDo - " + ProjectProperties::getProjectName());
    setStyleSheet("background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 #bfbfbf, stop: 1 #3e3e3e);");
    setCentralWidget(mainAppWidget);
    setWindowInCenter(this);

    mainAppWidget->createWidgets();

    changeScale();
    changeDrawedTilesCount();

    menuBar()->setStyleSheet("background-color: white");
    menuBar()->addMenu(fileMenu);

    statusBar()->setStyleSheet("background-color: white");
    statusBar()->addWidget(scaleLabel);
    statusBar()->addWidget(tilesCountLabel);
}


void MainWindow::changeScale()
{
    QString scale { QString::number(mainAppWidget->getDrawingWidget()->getScale()) };
    scaleLabel->setText("Scale: " + scale);
    statusBar()->update();
}


void MainWindow::changeDrawedTilesCount()
{
    QString tilesDrawed { QString::number(mainAppWidget->getDrawingWidget()->getDrawedTiles()) };
    QString tilesCount { QString::number(mainAppWidget->getDrawingWidget()->getTilesCount()) };
    tilesCountLabel->setText("Tiles: " + tilesDrawed + "/" + tilesCount);
    statusBar()->update();
}


void MainWindow::closeApp()
{
    qDebug() << "test";
}

