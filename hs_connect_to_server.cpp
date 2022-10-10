#include "hs_connect_to_server.h"
#include "ui_hs_connect_to_server.h"

Hs_connect_to_server::Hs_connect_to_server(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Hs_connect_to_server)
{
    ui->setupUi(this);
    initialize();
    initializeslots();
}

Hs_connect_to_server::~Hs_connect_to_server()
{
    delete ui;
}

void Hs_connect_to_server::on_connect_button_clicked()
{
    m_serverURL=new QString();
    *m_serverURL=m_server_address_input->text();

    if(*m_serverURL!="")
    {
        m_client=new Hs_OpcUAClient(*m_serverURL);
        sendclient(m_client);
        connect(m_client,SIGNAL(send_connect_status(QString)),this,SLOT(receive_connect_status(QString)));
    }

    close();
}

void Hs_connect_to_server::initialize()
{
    m_Label1=new QLabel();
    m_Label1->setText("服务器地址");

    m_server_address_input=new QLineEdit();
    m_server_address_input->setMinimumHeight(30);
    m_server_address_input->setText("opc.tcp://192.168.23.43:4842");

    m_connect_button=new QPushButton();
    m_connect_button->setText("连接设备");

    QHBoxLayout *Hlay1=new QHBoxLayout();
    Hlay1->addWidget(m_Label1);
    Hlay1->addWidget(m_server_address_input);

    QVBoxLayout *VLay1=new QVBoxLayout();
    VLay1->addLayout(Hlay1);
    VLay1->addWidget(m_connect_button);
    setLayout(VLay1);
}

void Hs_connect_to_server::receive_connect_status(QString status)
{
    sendstatus(status);
}

void Hs_connect_to_server::initializeslots()
{
    connect(m_connect_button,SIGNAL(clicked()),this,SLOT(on_connect_button_clicked()));
}
