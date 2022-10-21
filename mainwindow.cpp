#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "HsUI.h"
#include "HsMainWindow.h"

QMap<QString, QAction *> MainWindow::m_actionMap;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
//    initializeTab();
//    initializeUI();
//    initslots();
//    this->resize(1280,720);
//    setContextMenuPolicy(Qt::CustomContextMenu);
    initializeView();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::initializeTab()
{
    analyse=new Hs_analyse(this);
    analyse_action=new Hs_Analyse_Action();
    analyse_action->bindWidget(analyse);
    ui->tabWidget->addTab(analyse_action,"连接设备");
    ui->tabWidget->setTabBarAutoHide(true);
    ui->tabWidget->setContextMenuPolicy(Qt::CustomContextMenu);
}

void MainWindow::initializeUI()
{
    m_mainGLay=new QGridLayout (ui->widget);
    m_DownLeftLay=new QHBoxLayout();
    m_mainGLay->addLayout(m_DownLeftLay,0,0,8,8);
}


void MainWindow::initslots()
{
    connect(ui->tabWidget,&QTabWidget::tabBarDoubleClicked,this,&MainWindow::hidewindow);
}

void MainWindow::initializeView()
{
    this->setWindowIcon(QIcon(":/resource/icon/mainicon.png"));
    this->setWindowTitle("数据监控");

    ui->menuBar->clear(); // 不改动原先的内容
    auto &actionMap = MainWindow::getActionMap(); // 存储一下，方便调用

    // 创建菜单栏
    auto *fileMenu = ui->menuBar->addMenu(tr("&文件"));
    m_toolBar = this->addToolBar(tr("toolbar"));

    QAction *newAct = new QAction(QIcon(":/resource/icon/daochu.png"), tr("&新建"), this);
    newAct->setShortcuts(QKeySequence::New);
    newAct->setStatusTip(tr("Create a new file"));
    fileMenu->addAction(newAct);
    actionMap["Create"] = newAct;

    QAction *openAct = new QAction(QIcon(":/resource/icon/daoru.png"), tr("&打开"), this);
    openAct->setShortcuts(QKeySequence::Open);
    openAct->setStatusTip(tr("Open an existing file"));
    fileMenu->addAction(openAct);
    actionMap["Open"] = openAct;

    fileMenu->addSeparator();

    QAction *saveAct = new QAction(QIcon(":/resource/icon/baocun.png"), tr("&保存"), this);
    saveAct->setShortcuts(QKeySequence::Save);
    saveAct->setStatusTip(tr("Save the document to disk"));
    fileMenu->addAction(saveAct);
    actionMap["Save"] = saveAct;

    QAction *saveAsAct = new QAction(QIcon(":/resource/icon/baocun.png"), tr("&另存为"), this);
    saveAsAct->setShortcuts(QKeySequence::SaveAs);
    saveAsAct->setStatusTip(tr("Save the document under a new name"));
    fileMenu->addAction(saveAsAct);
    actionMap["SaveAs"] = saveAsAct;

    fileMenu->addSeparator();

    QAction *exitAct = new QAction(QIcon(":/resource/icon/daochu.png"), tr("&退出"), this);
    exitAct->setShortcuts(QKeySequence::Quit);
    exitAct->setStatusTip(tr("Exit the application"));
    fileMenu->addAction(exitAct);
    actionMap["Exit"] = exitAct;

    ui->menuBar->addMenu(tr("&视图"));

    auto *serverMenu = ui->menuBar->addMenu(tr("&数据监控"));

    QAction *connectAct = new QAction(QIcon(":/resource/icon/xinhaolianjie.png"), tr("&连接设备"), this);
    connectAct->setShortcuts(QKeySequence::SaveAs);
    connectAct->setStatusTip(tr("Connect to opc ua server"));
    serverMenu->addAction(connectAct);
    actionMap["Connect"] = connectAct;

    QAction *disconnectAct = new QAction(QIcon(":/resource/icon/lianjieduankai.png"), tr("&断开连接"), this);
    disconnectAct->setShortcuts(QKeySequence::SaveAs);
    disconnectAct->setStatusTip(tr("Disconnect from opc ua server"));
    serverMenu->addAction(disconnectAct);
    actionMap["Disconnect"] = disconnectAct;

    ui->menuBar->addMenu(tr("&工具"));
    ui->menuBar->addMenu(tr("&帮助"));

    QStringList toolBarList = { "Create", "Open", "Save", "SaveAs", "separator", "Exit" };

    m_toolbarMap[HsUI::HOMEPAGE] = QStringList({ "Create", "Open", "Save", "SaveAs", "separator", "Exit" });
    m_toolbarMap[HsUI::DATAMONITOR] = QStringList({ "Create", "Open", "Save", "SaveAs", "separator", "Connect", "Disconnect", "separator", "Exit" });
    m_toolbarMap[HsUI::DATAANALYSIS] = QStringList({ "Create", "Open", "Save", "SaveAs", "separator", "Exit" });

    this->updateToolBar(HsUI::HOMEPAGE);

    // 主界面
    m_hsMainWindow = new HsMainWindow(this);
    while (ui->centralWidget->layout()->itemAt(0)) {
        ui->centralWidget->layout()->removeItem(ui->centralWidget->layout()->itemAt(0));
    }
    ui->centralWidget->layout()->addWidget(m_hsMainWindow);
}

void MainWindow::updateToolBar(int viewType)
{
    if (m_toolbarMap[viewType].length() <= 0) return;

    const QStringList &list = m_toolbarMap[viewType];
    auto &actionMap = MainWindow::getActionMap();
    // 更新工具栏
    m_toolBar->clear();
    for (auto i = 0; i < list.length(); ++i) {
        if (list[i] == "separator") {
            m_toolBar->addSeparator();
            continue;
        }
        if (actionMap[list[i]]) {
            m_toolBar->addAction(actionMap[list[i]]);
        }
    }
}

void MainWindow::hidewindow()
{
    if(!b_hidebar)
    {
        ui->tabWidget->removeTab(0);
        QWidget *temp=new QWidget();
        ui->tabWidget->addTab(temp,"连接设备");
        ui->tabWidget->setMinimumHeight(10);
        b_hidebar=true;
    }
    else
    {
        ui->tabWidget->removeTab(0);
        ui->tabWidget->addTab(analyse_action,"连接设备");
        ui->tabWidget->setMinimumHeight(0);
        b_hidebar=false;
    }
}

void MainWindow::on_tabWidget_customContextMenuRequested(const QPoint &pos)
{
    Q_UNUSED(pos);
    QMenu *menulist=new QMenu(this);
    menulist->addAction(ui->actHideTab);
    menulist->exec(QCursor::pos());
    delete  menulist;
}

void MainWindow::on_actHideTab_triggered()
{
    hidewindow();
}

void MainWindow::on_actNodeSetting_triggered()
{
    analyse->node_select();
}

void MainWindow::on_actNewMachine_triggered()
{
    analyse->connect_to_server();
    connect(analyse->get_m_connect_to_server(),SIGNAL(sendstatus(QString)),analyse_action,SLOT(on_machine_changed(QString)));
}

void MainWindow::on_actHistoryData_triggered()
{
    analyse->create_historydata_window();
}

