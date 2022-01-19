#ifndef MAINMENUWG_H
#define MAINMENUWG_H

#include <QWidget>
#include <QLabel>
#include <QVBoxLayout>
#include <QCoreApplication>
#include "createprojectdialog.h"
#include "clickablelabel.h"
#include <QDebug>

class MainMenuWG : public QWidget
{
    Q_OBJECT
public:
    explicit MainMenuWG(QWidget *parent = nullptr);

private:
    QLabel* titleLabel;
    QLabel* copyrightLabel;
    QLabel* imageLabel;
    ClickableLabel* createProjectLabel;
    ClickableLabel* loadProjectLabel;
    ClickableLabel* exitLabel;

    CreateProjectDialog* createProjectDialog;

private:
    void initialize();
    void addToLayout();
    void connectUI();

private slots:
    int openProjectDialog();
    void createProject();
    void loadProject();

signals:
    void projectCreated();
};

#endif // MAINMENUWG_H
