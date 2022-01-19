#include "locationsdialog.h"
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QCloseEvent>
#include "ResourceHelper.h"
#include "indexerinterface.h"

LocationsDialog::LocationsDialog(QWidget* parent) : QDialog(parent)
{
    initialize();
    addToLayout();
    connectUI();
}


void LocationsDialog::initialize()
{
    const QString styles { loadQss("style.qss") };

    setFixedSize(220, 600);
    setWindowTitle("TileDo");
    setStyleSheet(loadQss("style.qss"));
    setWindowInCenter(this, QPoint{ 640, 0 });

    treeWidget = new QTreeWidget;
    treeWidget->setHeaderHidden(true);
    treeWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    treeWidget->setSelectionMode(QAbstractItemView::SingleSelection);
    treeWidget->setStyleSheet("background-color: white;");

    topItem = new QTreeWidgetItem;
    topItem->setText(0, "Locations");
    treeWidget->addTopLevelItem(topItem);

    addLocationBtn = new QPushButton("Add");
    addLocationBtn->setStyleSheet(styles);

    editLocationBtn = new QPushButton("Edit");
    editLocationBtn->setStyleSheet(styles);

    deleteLocationBtn = new QPushButton("Delete");
    deleteLocationBtn->setStyleSheet(styles);
}


void LocationsDialog::addToLayout()
{
    QHBoxLayout* btnLayout = new QHBoxLayout;
    QVBoxLayout* layout = new QVBoxLayout;

    btnLayout->addWidget(addLocationBtn);
    btnLayout->addWidget(editLocationBtn);
    btnLayout->addWidget(deleteLocationBtn);

    layout->addWidget(treeWidget);
    layout->addLayout(btnLayout);
    setLayout(layout);
}


void LocationsDialog::connectUI()
{
    connect(addLocationBtn, &QPushButton::clicked, this, &LocationsDialog::addLocation);
    connect(editLocationBtn, &QPushButton::clicked, this, &LocationsDialog::editLocation);
    connect(deleteLocationBtn, &QPushButton::clicked, this, &LocationsDialog::deleteLocation);
}


void LocationsDialog::closeEvent(QCloseEvent* event)
{
    event->ignore();
}




//------------------------------------------------SLOTS------------------------------------------------
void LocationsDialog::addLocation()
{
    addLocationBtn->setStyleSheet(CLICKED_BUTTON_STYLE);
    IndexerInterface::setIndex(IndexerInterface::SET_LOCATION);
    emit addingLocation();
}


void LocationsDialog::editLocation()
{
    if(topItem->childCount() != 0)
    {
        for(int i = 0; i < topItem->childCount(); ++i)
        {
            if(topItem->child(i)->isSelected())
            {
                emit editingLocation(i);
            }
        }
    }
}


void LocationsDialog::deleteLocation()
{
    if(topItem->childCount() != 0)
    {
        for(int i = 0; i < topItem->childCount(); ++i)
        {
            if(topItem->child(i)->isSelected())
            {
                emit deletingLocation(i);
                delete topItem->takeChild(i);
            }
        }
    }
}


void LocationsDialog::locationAdded(QString name)
{
    QTreeWidgetItem* item = new QTreeWidgetItem;
    item->setText(0, name);
    topItem->addChild(item);
    topItem->setExpanded(true);
}


void LocationsDialog::locationEdited(int index, QString name)
{
    topItem->child(index)->setText(0, name);
}
