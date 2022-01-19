#include "mainmenuwg.h"

MainMenuWG::MainMenuWG(QWidget *parent) : QWidget(parent)
{
    initialize();
    addToLayout();
    connectUI();
}


void MainMenuWG::initialize()
{
    const QString qss {
        "QLabel"
        "{"
        "font-size: 20px;"
        "color: white;"
        "background-color: transparent;"
        "font-weight: bold;"
        "padding: 5px;"
        "}"
        ""
        "QLabel:hover:!pressed"
        "{"
        "color: black;"
        "}"
    };

    titleLabel = new QLabel("TileDo ", this);
    titleLabel->setStyleSheet("QLabel{ font-size: 45px; background-color: transparent; color: white; font-weight: bold; }");
    titleLabel->setAlignment(Qt::AlignCenter);

    copyrightLabel = new QLabel("All rights reserved. Copyright (c) Kewin Woźny - 2020", this);
    copyrightLabel->setStyleSheet("QLabel{ font-size: 15px; background-color: transparent; color: white; font-weight: bold; }");
    copyrightLabel->setAlignment(Qt::AlignCenter | Qt::AlignBottom);

    imageLabel = new QLabel("IMAGE", this);
    imageLabel->setAlignment(Qt::AlignCenter);
    imageLabel->setStyleSheet(qss);

    createProjectLabel = new ClickableLabel(this);
    createProjectLabel->setText("Create a new project");
    createProjectLabel->setStyleSheet(qss);
    createProjectLabel->setAlignment(Qt::AlignCenter);

    loadProjectLabel = new ClickableLabel(this);
    loadProjectLabel->setText("Load existing project");
    loadProjectLabel->setStyleSheet(qss);
    loadProjectLabel->setAlignment(Qt::AlignCenter);

    exitLabel = new ClickableLabel(this);
    exitLabel->setText("Exit");
    exitLabel->setStyleSheet(qss);
    exitLabel->setAlignment(Qt::AlignCenter);

    createProjectDialog = new CreateProjectDialog(this);
}


void MainMenuWG::addToLayout()
{
    QVBoxLayout* layout = new QVBoxLayout;

    layout->setMargin(0);
    layout->setAlignment(Qt::AlignCenter);

    layout->addSpacing(50);
    layout->addWidget(titleLabel);
    layout->addSpacing(100);

    layout->addWidget(imageLabel);
    layout->addSpacing(100);

    layout->addWidget(createProjectLabel);
    layout->addWidget(loadProjectLabel);
    layout->addWidget(exitLabel);
    layout->addSpacing(200);

    layout->addWidget(copyrightLabel);

    setLayout(layout);
}


void MainMenuWG::connectUI()
{
    connect(createProjectLabel, &ClickableLabel::clicked, this, &MainMenuWG::openProjectDialog);
    connect(loadProjectLabel, &ClickableLabel::clicked, this, &MainMenuWG::loadProject);
    connect(createProjectDialog, &CreateProjectDialog::projectCreated, this, &MainMenuWG::createProject);
    connect(exitLabel, &ClickableLabel::clicked, this, &QCoreApplication::quit);
}


int MainMenuWG::openProjectDialog()
{
    return createProjectDialog->exec();
}


void MainMenuWG::createProject()
{
    emit projectCreated();
}


void MainMenuWG::loadProject()
{
    QFileDialog fileDialog(this);
    QStringList fileName;

    fileDialog.setFileMode(QFileDialog::ExistingFile);
    fileDialog.setNameFilter("Tiled Map (*.tmf)");
    fileDialog.setViewMode(QFileDialog::Detail);
    fileDialog.setDirectory(PROJECTS_DIR_PATH);

    if(fileDialog.exec())
        fileName = fileDialog.selectedFiles();

    if(!fileName.isEmpty())
    {
        if(ProjectProperties::loadProjectFile(fileName.at(0)))
            emit projectCreated();
        else
            QMessageBox::warning(createProjectDialog, "File error!", "Can't load a project file(check project properties in file).");
    }
}

