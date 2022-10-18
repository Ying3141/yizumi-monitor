#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    initializeTab();
    initializeUI();
    initslots();
    this->resize(1280,720);
    setContextMenuPolicy(Qt::CustomContextMenu);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::set_statusbartext(QString text)
{
    ui->statusBar->showMessage(text,5000);
}


void MainWindow::initializeTab()
{
    analyse=new Hs_analyse(this);
    analyse_action=new Hs_Analyse_Action();
    analyse_action->bindWidget(analyse);
    ui->tabWidget->addTab(analyse_action,"连接设备");
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
        ui->tabWidget->setMinimumHeight(120);
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

