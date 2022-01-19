#ifndef LOCATIONSDIALOG_H
#define LOCATIONSDIALOG_H

#include <QObject>
#include <QDialog>
#include <QTreeWidget>
#include <QPushButton>

class LocationsDialog : public QDialog
{
    Q_OBJECT

public:
    LocationsDialog(QWidget* parent = nullptr);

private:
    QTreeWidget* treeWidget;
    QTreeWidgetItem* topItem;
    QPushButton* addLocationBtn;
    QPushButton* editLocationBtn;
    QPushButton* deleteLocationBtn;

private:
    void initialize();
    void addToLayout();
    void connectUI();

protected:
    virtual void closeEvent(QCloseEvent *) override;

private slots:
    void addLocation();
    void editLocation();
    void deleteLocation();

public slots:
    void locationAdded(QString name);
    void locationEdited(int index, QString name);

signals:
    void addingLocation();
    void editingLocation(size_t index);
    void deletingLocation(size_t index);
};

#endif // LOCATIONSDIALOG_H
