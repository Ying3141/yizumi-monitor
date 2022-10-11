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
    m_TabWidget=new QTabWidget();

    analyse=new Hs_analyse(this);
    analyse_action=new Hs_Analyse_Action();
    analyse_action->bindWidget(analyse);
    m_TabWidget->addTab(analyse_action,"连接设备");

}

void MainWindow::initializeUI()
{
    m_mainVLay=new QGridLayout (ui->centralWidget);
    m_UpLay=new QHBoxLayout();
    m_DownLay=new QHBoxLayout();
    m_mainVLay->addLayout(m_UpLay,0,0,2,10);
    m_mainVLay->addLayout(m_DownLay,2,0,8,10);
    m_UpLay->addWidget(m_TabWidget);
}


void MainWindow::initslots()
{

}
