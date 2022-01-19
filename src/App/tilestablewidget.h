#ifndef TILESTABLEWIDGET_H
#define TILESTABLEWIDGET_H

#include <QDialog>
#include <QTableWidget>
#include <QCheckBox>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHeaderView>
#include <QCloseEvent>

class TilesTableWidget : public QDialog
{
    Q_OBJECT

public:
    explicit TilesTableWidget(QWidget *parent = nullptr);

    void addTilesToTable();

    int getCurrentTileIndex() const;

private:
    QTableWidget* table;
    QCheckBox* gridVisibleCheckBox;
    QCheckBox* locationsVisibleCheckBox;
    QPushButton* resetTileIndexBtn;
    QPushButton* removeTileBtn;
    int currentTileIndex;

private:
    void initialize();
    void addToLayout();
    void connectUI();

protected:
    virtual void closeEvent(QCloseEvent* event) override;

private slots:
    void selectTileIndex();
    void changeGridVisiblity();
    void changeLocationsVisiblity();
    void resetTileIndex();
    void deleteTile();

public slots:
    void releaseButtons();

signals:
    void showGrid();
    void hideGrid();
    void showLocations();
    void hideLocations();
};

#endif // TILESTABLEWIDGET_H
