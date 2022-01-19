#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QCoreApplication>
#include <QLabel>
#include <QMenu>
#include "ResourceHelper.h"
#include "mainmenuwg.h"
#include "mainappwg.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    MainMenuWG* mainMenuWidget;
    MainAppWG* mainAppWidget;
    QMenu* fileMenu;
    QLabel* scaleLabel;
    QLabel* tilesCountLabel;

private:
    void initialize();
    void connectUI();

protected:
    virtual void closeEvent(QCloseEvent* event) override;

private slots:
    void changeWidget();
    void changeScale();
    void changeDrawedTilesCount();
    void closeApp();
};
#endif // MAINWINDOW_H
