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

//void MainWindow::on_test2_clicked()
//{
//    testnode=m_client->m_client->node("ns=4;s=APPL.Injection1.sv_rScrewPositionAbs");
//    //testnode->readAttributes(QOpcUa::NodeAttribute::Value);

//    QOpcUaNode *node=m_client->m_client->node("ns=4;s=APPL.system.sv_iShotCounterAct");
//    connect(node,&QOpcUaNode::dataChangeOccurred,this,&MainWindow::on_update_data_clicked);

////    m_noid[0]->readAttributes(QOpcUa::NodeAttribute::Value);//更新参数
////    qDebug()<<"readnode"<<m_noid[0]->valueAttribute().value<float>();
////    qDebug()<<"value:"<<m_noid[0]->attribute(QOpcUa::NodeAttribute::Value);//读取更新后的参数
//    //ui->statusBar->showMessage(tr("临时信息!"),5000);
//}

void MainWindow::set_statusbartext(QString text)
{
    ui->statusBar->showMessage(text,5000);
}

void MainWindow::initializeTab()
{
    m_TabWidget=new QTabWidget();

    analyse=new Hs_analyse();
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

void MainWindow::on_create_analyse()
{
    if(m_table)
    {
        m_DownLay->removeWidget(m_table);
    }

    m_table=new QTableWidget(analyse->get_m_nodes().size()+1,1,this);

    QTableWidgetItem *headerItem;
    headerItem=new QTableWidgetItem("产品重量");
    m_table->setVerticalHeaderItem(0,headerItem);

    for(int i=0;i<analyse->get_m_nodes().size();i++)
    {
        headerItem=new QTableWidgetItem(analyse->get_m_nodes().at(i)->get_name());
        m_table->setVerticalHeaderItem(i+1,headerItem);
    }
    m_DownLay->addWidget(m_table);
}

void MainWindow::on_update_data()
{
        QOpcUaNode *node;
        QTableWidgetItem *headerItem;
        for(int i=0;i<analyse->get_m_nodes().size();i++)
        {
            node=analyse->get_m_client()->m_client->node(analyse->get_m_nodes().at(0)->get_node_id());
            //node=analyse->get_m_client()->m_client->node("ns=4;s=APPL.Injection1.sv_rScrewPositionAbs");

            MyThread *thread2=new MyThread(node);
            thread2->start();
            //停止线程
            thread2->quit();
            //等待线程处理完手头工作
            thread2->wait();

            qDebug()<<node->valueAttribute().value<float>();
            headerItem=new QTableWidgetItem(QString::number(node->valueAttribute().value<float>()));
            m_table->setItem(i+1,m_table->columnCount()-1,headerItem);
        }

        int curCol=m_table->columnCount();
        m_table->insertColumn(curCol);
}

void MainWindow::initslots()
{
    connect(analyse,&Hs_analyse::create_analyse,this,&MainWindow::on_create_analyse);//点击创建分析时创建表格
    connect(analyse,&Hs_analyse::update_data,this,&MainWindow::on_update_data);
}
