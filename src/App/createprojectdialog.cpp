#include "createprojectdialog.h"

CreateProjectDialog::CreateProjectDialog(QWidget* parent) : QDialog(parent)
{
    initialize();
    addToLayout();
    connectUI();
}


void CreateProjectDialog::initialize()
{
    const int coordEditWidth {50};
    const QString styles{ loadQss("style.qss") };

    setStyleSheet(styles);

    projectNameLabel = new QLabel("Project name:", this);
    projectNameLabel->setStyleSheet(styles);

    imageFileLabel = new QLabel("File:", this);
    imageFileLabel->setStyleSheet(styles);

    tileSizeLabel = new QLabel("Tile size(px):", this);
    tileSizeLabel->setStyleSheet(styles);

    tileXLabel = new QLabel("X:", this);
    tileXLabel->setStyleSheet(styles);

    tileYLabel = new QLabel("Y:", this);
    tileYLabel->setStyleSheet(styles);

    mapSizeLabel = new QLabel("Map size(tiles):", this);
    mapSizeLabel->setStyleSheet(styles);

    mapXLabel = new QLabel("X:", this);
    mapXLabel->setStyleSheet(styles);

    mapYLabel = new QLabel("Y:", this);
    mapYLabel->setStyleSheet(styles);

    projectNameEdit = new QLineEdit(this);
    projectNameEdit->setStyleSheet(styles);

    imageFileEdit = new QLineEdit(this);
    imageFileEdit->setStyleSheet(styles);
    imageFileEdit->setEnabled(false);

    tileXEdit = new QSpinBox(this);
    tileXEdit->setButtonSymbols(QAbstractSpinBox::NoButtons);
    tileXEdit->setFixedWidth(coordEditWidth);
    tileXEdit->setStyleSheet(styles);

    tileYEdit = new QSpinBox(this);
    tileYEdit->setButtonSymbols(QAbstractSpinBox::NoButtons);
    tileYEdit->setFixedWidth(coordEditWidth);
    tileYEdit->setStyleSheet(styles);

    mapXEdit = new QSpinBox(this);
    mapXEdit->setButtonSymbols(QAbstractSpinBox::NoButtons);
    mapXEdit->setFixedWidth(coordEditWidth);
    mapXEdit->setStyleSheet(styles);

    mapYEdit = new QSpinBox(this);
    mapYEdit->setButtonSymbols(QAbstractSpinBox::NoButtons);
    mapYEdit->setFixedWidth(coordEditWidth);
    mapYEdit->setStyleSheet(styles);

    chooseFileBtn = new QPushButton("Choose", this);
    chooseFileBtn->setStyleSheet(styles);

    createBtn = new QPushButton("Create", this);
    createBtn->setStyleSheet(styles);

    cancelBtn = new QPushButton("Cancel", this);
    cancelBtn->setStyleSheet(styles);
}


void CreateProjectDialog::addToLayout()
{
    QHBoxLayout* tileLayout = new QHBoxLayout;
    QHBoxLayout* mapLayout = new QHBoxLayout;
    QGridLayout* gridLayout = new QGridLayout;
    QHBoxLayout* btnLayout = new QHBoxLayout;
    QVBoxLayout* layout = new QVBoxLayout;

    tileLayout->addWidget(tileXLabel);
    tileLayout->addWidget(tileXEdit);
    tileLayout->addSpacing(10);
    tileLayout->addWidget(tileYLabel);
    tileLayout->addWidget(tileYEdit);

    mapLayout->addWidget(mapXLabel);
    mapLayout->addWidget(mapXEdit);
    mapLayout->addSpacing(10);
    mapLayout->addWidget(mapYLabel);
    mapLayout->addWidget(mapYEdit);

    gridLayout->addWidget(projectNameLabel, 0, 0);
    gridLayout->addWidget(projectNameEdit, 0, 1);
    gridLayout->addWidget(imageFileLabel, 1, 0);
    gridLayout->addWidget(imageFileEdit, 1, 1);
    gridLayout->addWidget(chooseFileBtn, 1, 2);
    gridLayout->addWidget(tileSizeLabel, 2, 0);
    gridLayout->addLayout(tileLayout, 3, 0);
    gridLayout->addWidget(mapSizeLabel, 4, 0);
    gridLayout->addLayout(mapLayout, 5, 0);

    btnLayout->setAlignment(Qt::AlignRight);
    btnLayout->addWidget(createBtn);
    btnLayout->addWidget(cancelBtn);

    layout->addLayout(gridLayout);
    layout->addLayout(btnLayout);

    setLayout(layout);
}


void CreateProjectDialog::connectUI()
{
    connect(chooseFileBtn, &QPushButton::clicked, this, &CreateProjectDialog::chooseFile);
    connect(createBtn, &QPushButton::clicked, this, &CreateProjectDialog::createProject);
    connect(cancelBtn, &QPushButton::clicked, this, &QDialog::close);
}


bool CreateProjectDialog::checkInput()
{
    if(projectNameEdit->text().isEmpty())
    {
        QMessageBox::warning(this, "Project name empty", "Please input a project name.");
        return false;
    }

    if(imageFileEdit->text().isEmpty())
    {
        QMessageBox::warning(this, "File not selected", "Please select a image file.");
        return false;
    }

    if(tileXEdit->value() == 0)
    {
        QMessageBox::warning(this, "Please set a tile width.", "Tile width can't be equal 0");
        return false;
    }

    if(tileYEdit->value() == 0)
    {
        QMessageBox::warning(this, "Please set a tile height.", "Tile height can't be equal 0");
        return false;
    }

    if(mapXEdit->value() == 0)
    {
        QMessageBox::warning(this, "Please set a map width.", "Map width can't be equal 0");
        return false;
    }

    if(mapYEdit->value() == 0)
    {
        QMessageBox::warning(this, "Please set a map height.", "Map height can't be equal 0");
        return false;
    }

    QString projectPath { PROJECTS_DIR_PATH + "/" + projectNameEdit->text() };
    QDir dir;

    if(dir.exists(projectPath))
    {
        QMessageBox::warning(this, "Ups...", "Project with this name already exists.");
        return false;
    }

    dir.mkdir(projectPath);

    return true;
}


void CreateProjectDialog::setProjectProperties()
{
    //TODO: Implement progress dialog, because app freezing for a few seconds

    ProjectProperties::initialize(
        projectNameEdit->text(),
        imageFileEdit->text(),
        QPoint{ tileXEdit->value(), tileYEdit->value() },
        QPoint{ mapXEdit->value(), mapYEdit->value() });

    ProjectProperties::createProjectFile();
    ProjectProperties::createTilesPoints();
    ProjectProperties::createTiles();
}


void CreateProjectDialog::chooseFile()
{
    QFileDialog fileDialog(this);
    QStringList fileName;

    fileDialog.setFileMode(QFileDialog::ExistingFile);
    fileDialog.setNameFilter("Images (*.png *.jpg)");
    fileDialog.setViewMode(QFileDialog::Detail);

    if(fileDialog.exec())
        fileName = fileDialog.selectedFiles();

    if(!fileName.empty())
        imageFileEdit->setText(fileName.at(0));
}


void CreateProjectDialog::createProject()
{
    if(checkInput())
    {
        setProjectProperties();
        emit projectCreated();
        close();
    }
}
