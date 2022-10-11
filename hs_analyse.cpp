#include "hs_analyse.h"
#include "ui_hs_analyse.h"

#include "mainwindow.h"
#include "ui_mainwindow.h"

Hs_analyse::Hs_analyse(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Hs_analyse)
{
    ui->setupUi(this);
    this->setAttribute(Qt::WA_TransparentForMouseEvents,true);
    m_parent = static_cast<MainWindow*>(parent);
}

Hs_analyse::~Hs_analyse()
{
    delete ui;
}

void Hs_analyse::connect_to_server()
{
    m_connect_to_server=new Hs_connect_to_server();
    connect(m_connect_to_server,SIGNAL(sendclient(Hs_OpcUAClient*)),this,SLOT(receive_client(Hs_OpcUAClient*)));
    m_connect_to_server->show();
}

void Hs_analyse::receive_client(Hs_OpcUAClient *m_client)
{
    this->m_client=m_client;

    m_shotcountNode=m_client->m_client->node("ns=4;s=APPL.system.sv_iShotCounterAct");//连接到周期参数，备用
    m_shotcountNode->enableMonitoring(QOpcUa::NodeAttribute::Value,0);//对周期参数进行监视
}

void Hs_analyse::node_select()
{
    m_node_select=new Hs_collect_setting(m_nodes);
    m_node_select->show();
}

void Hs_analyse::node_setting()
{
    m_node_setting=new Hs_Node_setting(m_nodes);
    m_node_setting->show();
}

void Hs_analyse::create_analyse()
{
    if(m_parent->m_table)
    {
        m_parent->m_DownLay->removeWidget(m_parent->m_table);
    }

    m_parent->m_table=new QTableWidget(m_parent->analyse->get_m_nodes().size()+1,1,this);

    QTableWidgetItem *headerItem;
    headerItem=new QTableWidgetItem("产品重量");
    m_parent->m_table->setVerticalHeaderItem(0,headerItem);

    for(int i=0;i<m_parent->analyse->get_m_nodes().size();i++)
    {
        headerItem=new QTableWidgetItem(m_parent->analyse->get_m_nodes().at(i)->get_name());
        m_parent->m_table->setVerticalHeaderItem(i+1,headerItem);
    }
    m_parent->m_DownLay->addWidget(m_parent->m_table);
}

void Hs_analyse::update_data()
{
    connect(m_shotcountNode,&QOpcUaNode::dataChangeOccurred,this,&Hs_analyse::test2);

    //testnode=m_client->m_client->node("ns=4;s=APPL.Injection1.sv_InjectProfVis.Profile.Points[1].rPressure");
    //testnode=m_parent->analyse->get_m_client()->m_client->node("ns=4;s=APPL.Injection1.sv_rScrewPositionAbs");
    qDebug()<<"works";

//    for(int i=0;i<m_parent->analyse->get_m_nodes().size();i++)
//    {
//        testnode=m_parent->analyse->get_m_client()->m_client->node(m_parent->analyse->get_m_nodes().at(i)->get_node_id());
//        connect(testnode,&QOpcUaNode::attributeRead,this,&Hs_analyse::test2);
//        testnode->readAttributes(QOpcUa::NodeAttribute::Value);
//        qDebug()<<testnode->valueAttribute().value<float>();
//        disconnect(testnode);
//    }

//    testnode=m_parent->analyse->get_m_client()->m_client->node("ns=4;s=APPL.Injection1.sv_InjectProfVis.Profile.Points[1].rPressure");
//    connect(testnode,&QOpcUaNode::attributeRead,this,&Hs_analyse::test2);
//    testnode->readAttributes(QOpcUa::NodeAttribute::Value);
//    disconnect(testnode);


//    testnode=m_parent->analyse->get_m_client()->m_client->node("ns=4;s=APPL.Injection1.sv_rScrewPositionAbs");
//    connect(testnode,&QOpcUaNode::attributeRead,this,&Hs_analyse::test2);
//    testnode->readAttributes(QOpcUa::NodeAttribute::Value);
//    disconnect(testnode);


//    testnode=m_parent->analyse->get_m_client()->m_client->node("ns=4;s=APPL.Injection1.sv_InjectProfVis.Profile.Points[1].rPressure");
//    connect(testnode,&QOpcUaNode::attributeRead,this,&Hs_analyse::test2);
//    testnode->readAttributes(QOpcUa::NodeAttribute::Value);
//    disconnect(testnode);


//新建线程，运行线程，停止线程和等待线程
//    MyThread_2 *thread2=new MyThread_2(testnode);
//    thread2->start();
//    thread2->quit();
//    thread2->wait();


    //node=m_parent->analyse->get_m_client()->m_client->node("ns=4;s=APPL.Injection1.sv_rScrewPositionAbs");

//    MyThread *thread=new MyThread(testnode);
//    thread->start();
//    thread->wait();
//    thread->quit();


//    qDebug()<<testnode->valueAttribute().value<float>();
//    headerItem=new QTableWidgetItem(QString::number(testnode->valueAttribute().value<float>()));
//    m_parent->m_table->setItem(1,m_parent->m_table->columnCount()-1,headerItem);

//    int curCol=m_parent->m_table->columnCount();
//    m_parent->m_table->insertColumn(curCol);
}

void Hs_analyse::test1()//测试写
{
    testnode=m_parent->analyse->get_m_client()->m_client->node("ns=4;s=APPL.Injection1.sv_InjectProfVis.Profile.Points[1].rPressure");
    QOpcUa::NodeAttribute attribute ;
    attribute = QOpcUa::NodeAttribute::Value;
    QVariant var=130;
    testnode->writeAttribute(attribute,var,QOpcUa::Types::Float);
    qDebug()<<"works1";

}

void Hs_analyse::test2()//测试接受数据变化信号
{
    qDebug()<<"works2";
    int curCol=m_parent->m_table->columnCount();
    m_parent->m_table->insertColumn(curCol);

//    QTableWidgetItem *headerItem;
//    headerItem=new QTableWidgetItem(QString::number(testnode->valueAttribute().value<float>()));
//    m_parent->m_table->setItem(i+1,m_parent->m_table->columnCount()-1,headerItem);
}

QVector<hs_node*> Hs_analyse::get_m_nodes()
{
    return m_nodes;
}

Hs_OpcUAClient* Hs_analyse::get_m_client()
{
    return m_client;
}
