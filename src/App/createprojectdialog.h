#ifndef CREATEPROJECTDIALOG_H
#define CREATEPROJECTDIALOG_H

#include <QObject>
#include <QDialog>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QMessageBox>
#include <QFileDialog>
#include <QSpinBox>
#include "ResourceHelper.h"

class CreateProjectDialog : public QDialog
{
    Q_OBJECT

public:
    CreateProjectDialog(QWidget* parent = nullptr);

private:
    QLabel* projectNameLabel;
    QLabel* imageFileLabel;
    QLabel* tileSizeLabel;
    QLabel* tileXLabel;
    QLabel* tileYLabel;
    QLabel* mapSizeLabel;
    QLabel* mapXLabel;
    QLabel* mapYLabel;
    QLineEdit* projectNameEdit;
    QLineEdit* imageFileEdit;
    QSpinBox* tileXEdit;
    QSpinBox* tileYEdit;
    QSpinBox* mapXEdit;
    QSpinBox* mapYEdit;
    QPushButton* chooseFileBtn;
    QPushButton* createBtn;
    QPushButton* cancelBtn;

private:
    void initialize();
    void addToLayout();
    void connectUI();

    bool checkInput();
    void setProjectProperties();

private slots:
    void chooseFile();
    void createProject();

signals:
    void projectCreated();
};

#endif // CREATEPROJECTDIALOG_H
