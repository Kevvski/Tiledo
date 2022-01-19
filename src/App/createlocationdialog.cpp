#include "createlocationdialog.h"
#include <QGridLayout>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QResizeEvent>
#include <QColorDialog>
#include <QMessageBox>

CreateLocationDialog::CreateLocationDialog(bool editLocation, QWidget* parent) : QDialog(parent)
{
    initialize(editLocation);
    addToLayout();
    connectUI();
}


void CreateLocationDialog::setLocationPosition(const QPoint &point)
{
    xBox->setValue(point.x());
    yBox->setValue(point.y());
}


void CreateLocationDialog::setColor(const QColor &color)
{
    selectedColor = color;
    changeBtnColor();
}


void CreateLocationDialog::setLocationName(const QString &text)
{
    nameEdit->setText(text);
}


void CreateLocationDialog::setDiameter(int diameter)
{
    diameterBox->setValue(diameter);
}


void CreateLocationDialog::initialize(bool editLocation)
{
    const QString styles { loadQss("style.qss") };

    setStyleSheet(styles);
    setFixedSize(400, 250);

    nameLabel = new QLabel("Location name:");

    xLabel = new QLabel("X:");

    yLabel = new QLabel("Y:");

    colorLabel = new QLabel("Color:");

    diameterLabel = new QLabel("Diameter:");

    nameEdit = new QLineEdit;

    xBox = new QSpinBox;
    xBox->setStyleSheet(styles);
    xBox->setFixedWidth(100);
    xBox->setRange(0, 10000);

    yBox = new QSpinBox;
    yBox->setFixedWidth(100);
    yBox->setRange(0, 10000);

    diameterBox = new QSpinBox;
    diameterBox->setFixedWidth(100);
    diameterBox->setRange(1, 100);
    diameterBox->setValue(10);

    acceptBtn = new QPushButton("Add");

    if(editLocation)
        acceptBtn->setText("Update");

    cancelBtn = new QPushButton("Cancel");

    colorBtn = new QPushButton;
    colorBtn->setStyleSheet("background-color: red;");

    selectedColor = Qt::red;
}


void CreateLocationDialog::addToLayout()
{
    QGridLayout* layout = new QGridLayout;
    QGridLayout* coordsLayout = new QGridLayout;
    QHBoxLayout* btnLayout = new QHBoxLayout;

    coordsLayout->setVerticalSpacing(8);
    coordsLayout->addWidget(xLabel, 0, 0);
    coordsLayout->addWidget(xBox, 0, 1);
    coordsLayout->addWidget(yLabel, 1, 0);
    coordsLayout->addWidget(yBox, 1, 1);
    coordsLayout->addWidget(colorLabel, 2, 0);
    coordsLayout->addWidget(colorBtn, 2, 1);
    coordsLayout->addWidget(diameterLabel, 3, 0);
    coordsLayout->addWidget(diameterBox, 3, 1);

    btnLayout->setAlignment(Qt::AlignRight);
    btnLayout->addWidget(acceptBtn);
    btnLayout->addWidget(cancelBtn);

    layout->addWidget(nameLabel, 0, 0);
    layout->addWidget(nameEdit, 0, 1);
    layout->addLayout(coordsLayout, 1, 0);
    layout->addLayout(btnLayout, 2, 1, Qt::AlignBottom);

    setLayout(layout);
}


void CreateLocationDialog::connectUI()
{
    connect(acceptBtn, &QPushButton::clicked, this, &CreateLocationDialog::addLocation);
    connect(cancelBtn, &QPushButton::clicked, this, &QDialog::close);
    connect(colorBtn, &QPushButton::clicked, this, &CreateLocationDialog::changeLocationColor);
}


void CreateLocationDialog::changeBtnColor()
{
    QString resultColor{ "background-color: rgb(" };

    resultColor += QString::number(selectedColor.red()) + ", ";
    resultColor += QString::number(selectedColor.green()) + ", ";
    resultColor += QString::number(selectedColor.blue());
    resultColor += ");";

    colorBtn->setStyleSheet(resultColor);
}


const QString CreateLocationDialog::getLocationName() const
{
    if(!nameEdit->text().isEmpty())
    {
        QString result = nameEdit->text().replace(" ", "_");
        return result;
    }
}


const QPoint CreateLocationDialog::getLocationPosition() const
{
    return QPoint{ xBox->value(), yBox->value() };
}


const QColor& CreateLocationDialog::getColor() const
{
    return selectedColor;
}


int CreateLocationDialog::getDiameter() const
{
    return diameterBox->value();
}




//------------------------------------------------SLOTS------------------------------------------------
void CreateLocationDialog::changeLocationColor()
{
    QColorDialog dialog;
    dialog.setCurrentColor(QColor{ Qt::red });

    if(dialog.exec())
    {
        selectedColor = dialog.selectedColor();
        changeBtnColor();
    }
}


void CreateLocationDialog::addLocation(){
    if(!nameEdit->text().isEmpty())
        emit done(QDialog::Accepted);
    else
        QMessageBox::information(this, "Ups...", "Please type name for location.");
}
