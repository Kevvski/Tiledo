#include "tilestablewidget.h"
#include "ResourceHelper.h"
#include "indexerinterface.h"

TilesTableWidget::TilesTableWidget(QWidget *parent) : QDialog(parent), currentTileIndex{ -1 }
{
    initialize();
    addToLayout();
    connectUI();
}


void TilesTableWidget::initialize()
{
    setFixedSize(220, 600);
    setWindowTitle("TileDo");
    setStyleSheet(loadQss("style.qss"));
    setWindowInCenter(this, QPoint{ -640, 0 });

    table = new QTableWidget;
    table->setStyleSheet("QTableWidget{ background-color: white; color: black; }");
    table->verticalHeader()->hide();
    table->setColumnCount(1);
    table->setSelectionMode(QAbstractItemView::SingleSelection);
    table->setHorizontalHeaderLabels(QStringList{ "Tiles" });
    table->setEditTriggers(QAbstractItemView::NoEditTriggers);
    table->setFixedWidth(100);

    gridVisibleCheckBox = new QCheckBox;
    gridVisibleCheckBox->setText("Show grid");
    gridVisibleCheckBox->setStyleSheet("QCheckBox{ color: white; }");
    gridVisibleCheckBox->setChecked(true);

    locationsVisibleCheckBox = new QCheckBox;
    locationsVisibleCheckBox->setText("Show locations");
    locationsVisibleCheckBox->setStyleSheet("QCheckBox{ color: white; }");
    locationsVisibleCheckBox->setChecked(true);

    resetTileIndexBtn = new QPushButton("Arrow");
    resetTileIndexBtn->setStyleSheet(CLICKED_BUTTON_STYLE);

    removeTileBtn = new QPushButton("Delete");
    removeTileBtn->setStyleSheet(loadQss("style.qss"));
}


void TilesTableWidget::addToLayout()
{
    QHBoxLayout* layout = new QHBoxLayout;
    QVBoxLayout* optionsLayout = new QVBoxLayout;

    optionsLayout->setAlignment(Qt::AlignTop);
    optionsLayout->addWidget(resetTileIndexBtn);
    optionsLayout->addWidget(removeTileBtn);
    optionsLayout->addWidget(gridVisibleCheckBox);
    optionsLayout->addWidget(locationsVisibleCheckBox);

    layout->addWidget(table);
    layout->addLayout(optionsLayout);
    setLayout(layout);
}


void TilesTableWidget::connectUI()
{
    connect(table, &QTableWidget::itemClicked, this, &TilesTableWidget::selectTileIndex);
    connect(gridVisibleCheckBox, &QCheckBox::clicked, this, &TilesTableWidget::changeGridVisiblity);
    connect(locationsVisibleCheckBox, &QCheckBox::clicked, this, &TilesTableWidget::changeLocationsVisiblity);
    connect(resetTileIndexBtn, &QPushButton::clicked, this, &TilesTableWidget::resetTileIndex);
    connect(removeTileBtn, &QPushButton::clicked, this, &TilesTableWidget::deleteTile);
}


void TilesTableWidget::addTilesToTable()
{
    const auto TILES_COUNT { ProjectProperties::getTilesCount() };

    table->setRowCount(TILES_COUNT);

    for(size_t i = 0; i < TILES_COUNT; ++i)
    {
        try
        {
            table->setItem(i, 0, new QTableWidgetItem(QIcon(ProjectProperties::getPixmap(i)), QString::number(i)));
        }
        catch (const std::out_of_range& e)
        {
            qDebug() << e.what();
        }
    }
}


int TilesTableWidget::getCurrentTileIndex() const
{
    return currentTileIndex;
}


void TilesTableWidget::closeEvent(QCloseEvent *event)
{
    event->ignore();
}




//------------------------------------------------SLOTS------------------------------------------------
void TilesTableWidget::selectTileIndex()
{
    QItemSelectionModel* selectItem = table->selectionModel();
    if(selectItem->hasSelection())
    {
        IndexerInterface::setIndex(table->model()->index(table->currentIndex().row(), 0).data().toInt());
        resetTileIndexBtn->setStyleSheet(loadQss("style.qss"));
        removeTileBtn->setStyleSheet(loadQss("style.qss"));
    }
}


void TilesTableWidget::changeGridVisiblity()
{
    if(gridVisibleCheckBox->isChecked())
        emit showGrid();
    else
        emit hideGrid();
}


void TilesTableWidget::changeLocationsVisiblity()
{
    if(locationsVisibleCheckBox->isChecked())
        emit showLocations();
    else
        emit hideLocations();
}


void TilesTableWidget::resetTileIndex()
{
    //TODO: Create a static string object for stylesheet
    resetTileIndexBtn->setStyleSheet(CLICKED_BUTTON_STYLE);
    removeTileBtn->setStyleSheet(loadQss("style.qss"));
    IndexerInterface::setIndex(IndexerInterface::NORMAL);
}

void TilesTableWidget::deleteTile()
{
    removeTileBtn->setStyleSheet(CLICKED_BUTTON_STYLE);
    resetTileIndexBtn->setStyleSheet(loadQss("style.qss"));
    IndexerInterface::setIndex(IndexerInterface::DELETE);
}


void TilesTableWidget::releaseButtons()
{
    resetTileIndexBtn->setStyleSheet(loadQss("style.qss"));
    removeTileBtn->setStyleSheet(loadQss("style.qss"));
}
