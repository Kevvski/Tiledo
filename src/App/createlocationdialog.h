#ifndef CREATELOCATIONDIALOG_H
#define CREATELOCATIONDIALOG_H

#include <QObject>
#include <QDialog>
#include <QLabel>
#include <QLineEdit>
#include <QSpinBox>
#include <QPushButton>
#include "ResourceHelper.h"

class CreateLocationDialog : public QDialog
{
    Q_OBJECT

public:
    CreateLocationDialog(bool editLocation = false, QWidget* parent = nullptr);

    void setLocationPosition(const QPoint& point);
    void setColor(const QColor& color);
    void setLocationName(const QString& text);
    void setDiameter(int diameter);

    const QString getLocationName() const;
    const QPoint getLocationPosition() const;
    const QColor& getColor() const;
    int getDiameter() const;

private:
    QLabel* nameLabel;
    QLabel* xLabel;
    QLabel* yLabel;
    QLabel* colorLabel;
    QLabel* diameterLabel;
    QLineEdit* nameEdit;
    QSpinBox* xBox;
    QSpinBox* yBox;
    QSpinBox* diameterBox;
    QPushButton* acceptBtn;
    QPushButton* cancelBtn;
    QPushButton* colorBtn;
    QColor selectedColor;

private:
    void initialize(bool editLocation = false);
    void addToLayout();
    void connectUI();
    void changeBtnColor();

private slots:
    void changeLocationColor();
    void addLocation();
};

#endif // CREATELOCATIONDIALOG_H
