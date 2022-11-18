#include "HsMainWindow.h"
#include "ui_HsMainWindow.h"

#include <QSplitter>
#include <QTreeWidgetItem>

#include "HsUI.h"
#include "mainwindow.h"
#include "HsHomePage.h"
#include "HsBasicInfo.h"
#include "HsMonitoring.h"
#include "HsAnalysis.h"

HsMainWindow::HsMainWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::HsMainWindow)
{
    ui->setupUi(this);

    mainWindow = static_cast<MainWindow *>(parent);

    initializeView();
    initSignalSlots();
}

HsMainWindow::~HsMainWindow()
{
    delete ui;
}

void HsMainWindow::addTreeItem(QTreeWidgetItem *parent, CustomTreeItemModel *item)
{
    QTreeWidgetItem *treeItem = new QTreeWidgetItem(parent, item->id);
    treeItem->setText(0, item->label);
    m_treeWidgetItemMap[treeItem] = item;

}

void HsMainWindow::constructTreeModel()
{
    root = new CustomTreeItemModel;
    root->viewType = HsUI::HOMEPAGE;
    root->label = "项目";
    root->type = "view";

    CustomTreeItemModel *machine = new CustomTreeItemModel;
    machine->viewType = HsUI::MACHINEINFO;
    machine->label = "机器1";
    machine->type = "view";
    machine->parent = root;
    root->children.push_back(machine);

    CustomTreeItemModel *basic = new CustomTreeItemModel;
    basic->viewType = HsUI::BASICINFO;
    basic->label = "基本信息";
    basic->type = "view";
    basic->parent = machine;
    machine->children.push_back(basic);

    CustomTreeItemModel *monitor = new CustomTreeItemModel;
    monitor->viewType = HsUI::DATAMONITOR;
    monitor->label = "数据监控";
    monitor->type = "view";
    monitor->parent = machine;
    machine->children.push_back(monitor);

    CustomTreeItemModel *analysis = new CustomTreeItemModel;
    analysis->viewType = HsUI::DATAANALYSIS;
    analysis->label = "数据分析";
    analysis->type = "view";
    analysis->parent = machine;
    machine->children.push_back(analysis);
}

void HsMainWindow::initializeView()
{

    // 构建树视图
    constructTreeModel();
    if (root) {
        QTreeWidgetItem *rootItem = new QTreeWidgetItem(ui->treeWidget, root->id);
        rootItem->setText(0, root->label);
        m_treeWidgetItemMap[rootItem] = root;
        createTreeItem(rootItem, root->children);
    }

    // 一些基本样式调整
    ui->treeWidget->setHeaderHidden(true);
    ui->treeWidget->expandAll();

    // 视图
    // create splitter window
    QSplitter *horiSplitter = new QSplitter(Qt::Horizontal, nullptr);
    horiSplitter->setHandleWidth(2);
    horiSplitter->setChildrenCollapsible(false);

    horiSplitter->addWidget(ui->treeWidget);
    horiSplitter->addWidget(ui->stackedWidget);

    this->layout()->addWidget(horiSplitter);

    // 首页
    auto *home = new HsHomePage;
    ui->stackedWidget->addWidget(home);
    m_widgetMap[HsUI::HOMEPAGE] = home;

    // 基本信息
    auto *basic = new HsBasicInfo;
    ui->stackedWidget->addWidget(basic);
    m_widgetMap[HsUI::BASICINFO] = basic;

    // 数据监控
    auto *monitoring = new HsMonitoring;
    ui->stackedWidget->addWidget(monitoring);
    m_widgetMap[HsUI::DATAMONITOR] = monitoring;

    // 数据分析
    auto *analysis = new HsAnalysis;
    ui->stackedWidget->addWidget(analysis);
    m_widgetMap[HsUI::DATAANALYSIS] = analysis;

    ui->stackedWidget->setCurrentWidget(home);

    connect(monitoring,&HsMonitoring::send_statistic_data,analysis,&HsAnalysis::on_statistic_data_receive);
    connect(monitoring,&HsMonitoring::send_newmold_signal,analysis,&HsAnalysis::on_newMold_signal_receive);
}

void HsMainWindow::initSignalSlots()
{
    connect(ui->treeWidget, &QTreeWidget::itemClicked, this, &HsMainWindow::onItemClicked);
}

void HsMainWindow::createTreeItem(QTreeWidgetItem *parent, QList<CustomTreeItemModel *> &children)
{
    if (parent == nullptr || children.length() == 0) return;

    for (auto i = 0; i < children.length(); ++i) {
        QTreeWidgetItem *item = new QTreeWidgetItem(parent, children[i]->viewType);
        item->setText(0, children[i]->label);
        m_treeWidgetItemMap[item] = children[i];
//        if (children[i]->type == "create") {
//            item->setForeground(0, Qt::blue);
//            if (children.length() > 1) {
//                item->setHidden(true);
//            } else {
//                item->setHidden(false);
//            }
//        }
        createTreeItem(item, children[i]->children);
    }
}

void HsMainWindow::onItemClicked(QTreeWidgetItem *item, int column)
{
    if (m_treeWidgetItemMap[item] == nullptr) return;

    ui->stackedWidget->setCurrentWidget(m_widgetMap[item->type()]);

    mainWindow->updateToolBar(item->type());
}
