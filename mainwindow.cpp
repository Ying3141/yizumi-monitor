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

void MainWindow::on_connect_to_server_clicked()
{
    Hs_connect_to_server *connect_to_server=new Hs_connect_to_server();
    connect(connect_to_server,SIGNAL(sendclient(Hs_OpcUAClient*)),this,SLOT(receive_client(Hs_OpcUAClient*)));
    connect(connect_to_server,SIGNAL(sendstatus(QString)),this,SLOT(set_statusbartext(QString)));
    connect_to_server->show();
}

void MainWindow::on_create_analyse_clicked()
{
//    Hs_analyse *analyse=new Hs_analyse();
//    analyse->show();
    m_table=new QTableWidget(m_nodes.size()+1,1,this);

    QTableWidgetItem *headerItem;
    headerItem=new QTableWidgetItem("产品重量");
    m_table->setVerticalHeaderItem(0,headerItem);
    for(int i=0;i<m_nodes.size();i++)
    {
        headerItem=new QTableWidgetItem(m_nodes.at(i)->get_name());
        m_table->setVerticalHeaderItem(i+1,headerItem);
    }

    m_DownLay->addWidget(m_table);
}

void MainWindow::on_node_clicked()
{
    Hs_collect_setting *setting=new Hs_collect_setting(m_nodes);
    setting->show();
}

void MainWindow::on_update_data_clicked()
{
    QOpcUaNode *node;
    QTableWidgetItem *headerItem;
    for(int i=0;i<m_nodes.size();i++)
    {
        //node=m_client->m_client->node(m_nodes[i]->get_node_id());
        testnode=m_client->m_client->node("ns=4;s=APPL.Injection1.sv_rScrewPositionAbs");
        MyThread *thread2=new MyThread(testnode);
        thread2->start();
        //停止线程
        thread2->quit();
        //等待线程处理完手头工作
        thread2->wait();

        qDebug()<<testnode->valueAttribute().value<float>();
        headerItem=new QTableWidgetItem(QString::number(testnode->valueAttribute().value<float>()));
        m_table->setItem(i+1,m_table->columnCount()-1,headerItem);
    }

    int curCol=m_table->columnCount();
    m_table->insertColumn(curCol);

}

void MainWindow::on_test2_clicked()
{
    testnode=m_client->m_client->node("ns=4;s=APPL.Injection1.sv_rScrewPositionAbs");
    //testnode->readAttributes(QOpcUa::NodeAttribute::Value);

    QOpcUaNode *node=m_client->m_client->node("ns=4;s=APPL.system.sv_iShotCounterAct");
    connect(node,&QOpcUaNode::dataChangeOccurred,this,&MainWindow::on_update_data_clicked);

//    m_noid[0]->readAttributes(QOpcUa::NodeAttribute::Value);//更新参数
//    qDebug()<<"readnode"<<m_noid[0]->valueAttribute().value<float>();
//    qDebug()<<"value:"<<m_noid[0]->attribute(QOpcUa::NodeAttribute::Value);//读取更新后的参数
    //ui->statusBar->showMessage(tr("临时信息!"),5000);
}

void MainWindow::receive_client(Hs_OpcUAClient *client)
{
    m_client=client;
}

void MainWindow::set_statusbartext(QString text)
{
    ui->statusBar->showMessage(text,5000);
}

void MainWindow::initializeConnect()
{
    m_connect_setting=new QWidget();
    m_connect_to_server=new QPushButton();
    m_disconnect_to_server=new QPushButton();
    m_test=new QPushButton();
    m_test2=new QPushButton();
    m_connect_to_server->setFixedSize(60,80);
    m_disconnect_to_server->setFixedSize(60,80);
    m_test->setFixedSize(60,80);
    m_test2->setFixedSize(60,80);
    m_connect_to_server->setText("连接\n设备");
    m_disconnect_to_server->setText("断开\n连接");
    m_test->setText("采集\n数据");
    m_test2->setText("测试2");



    QHBoxLayout *HLay=new QHBoxLayout(m_connect_setting);
    HLay->addWidget(m_connect_to_server);
    HLay->addWidget(m_disconnect_to_server);
    HLay->addWidget(m_test);
    HLay->addWidget(m_test2);
    HLay->addStretch();

}

void MainWindow::initializeAnalyse()
{
    m_analyse=new QWidget();
    m_create_analyse=new QPushButton();
    m_create_analyse->setText("创建\n分析");
    m_create_analyse->setFixedSize(60,80);
    QHBoxLayout *HLay=new QHBoxLayout(m_analyse);
    HLay->addWidget(m_create_analyse);
    HLay->addStretch();
}

void MainWindow::initializeSetting()
{

    m_node_setting=new QWidget();
    m_node=new QPushButton();
    m_node->setText("节点\n设置");
    m_node->setFixedSize(60,80);
    QHBoxLayout *HLay=new QHBoxLayout(m_node_setting);
    HLay->addWidget(m_node);
    HLay->addStretch();
}

void MainWindow::initializeTab()
{
    m_TabWidget=new QTabWidget();

    initializeConnect();
    initializeAnalyse();
    initializeSetting();

    m_TabWidget->addTab(m_connect_setting,"连接设备");
    m_TabWidget->addTab(m_node_setting,"配置信息");
    m_TabWidget->addTab(m_analyse,"相关分析");
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
    connect(m_connect_to_server,SIGNAL(clicked()),this,SLOT(on_connect_to_server_clicked()));
    connect(m_create_analyse,SIGNAL(clicked()),this,SLOT(on_create_analyse_clicked()));
    connect(m_node,SIGNAL(clicked()),this,SLOT(on_node_clicked()));
    connect(m_test,SIGNAL(clicked()),this,SLOT(on_update_data_clicked()));
    connect(m_test2,SIGNAL(clicked()),this,SLOT(on_test2_clicked()));
}
