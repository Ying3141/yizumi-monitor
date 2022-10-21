#ifndef HSMAINWINDOW_H
#define HSMAINWINDOW_H

#include <QWidget>
#include "hs_historydata.h"

struct CustomTreeItemModel {
    CustomTreeItemModel *parent = nullptr;
    int id;
    int viewType;
    QString label;
    QString type;
    QList<CustomTreeItemModel *> children;
};

class MainWindow;
class QTreeWidgetItem;

namespace Ui {
class HsMainWindow;
}

class HsMainWindow : public QWidget
{
    Q_OBJECT

public:
    explicit HsMainWindow(QWidget *parent = nullptr);
    ~HsMainWindow();

public:
    void addTreeItem(QTreeWidgetItem *parent, CustomTreeItemModel *item);

private:
    void constructTreeModel();
    void initializeView();
    void initSignalSlots();
    void createTreeItem(QTreeWidgetItem *parent, QList<CustomTreeItemModel *> &children);

private slots:
    void onItemClicked(QTreeWidgetItem *item, int column);

private:
    Ui::HsMainWindow *ui;
    MainWindow *mainWindow = nullptr;

    CustomTreeItemModel *root = nullptr;
    QHash<QTreeWidgetItem *, CustomTreeItemModel *> m_treeWidgetItemMap;
    QHash<int, QWidget *> m_widgetMap;

};

#endif // HSMAINWINDOW_H
