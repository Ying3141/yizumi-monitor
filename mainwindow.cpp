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
//    m_TabWidget=new QTabWidget();
//    m_TabWidget->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Fixed);
//    analyse=new Hs_analyse(this);
//    analyse_action=new Hs_Analyse_Action();
//    analyse_action->bindWidget(analyse);
//    m_TabWidget->addTab(analyse_action,"连接设备");

    analyse=new Hs_analyse(this);
    analyse_action=new Hs_Analyse_Action();
    analyse_action->bindWidget(analyse);
    ui->tabWidget->addTab(analyse_action,"连接设备");
}

void MainWindow::initializeUI()
{
    m_mainGLay=new QGridLayout (ui->widget);
//    m_UpLay=new QHBoxLayout();
    m_DownLeftLay=new QHBoxLayout();
    m_DownRightLay=new QHBoxLayout();
//    m_mainGLay->addLayout(m_UpLay,0,0,2,10);
    m_mainGLay->addLayout(m_DownLeftLay,0,0,8,8);
    m_mainGLay->addLayout(m_DownRightLay,0,8,8,2);
//    m_UpLay->addWidget(m_TabWidget);
}


void MainWindow::initslots()
{
    connect(ui->tabWidget,&QTabWidget::tabBarDoubleClicked,this,&MainWindow::testslot);
}

void MainWindow::testslot()
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
