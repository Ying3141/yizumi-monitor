#ifndef HS_ANALYSE_H
#define HS_ANALYSE_H

#include <QWidget>
#include <QTableWidget>
#include "hs_connect_to_server.h"
#include "hs_collect_setting.h"
#include "hs_node_setting.h"
#include "hs_thread.h"
#include "hs_thread2.h"
#include "windows.h"
#include <QMap>

class MainWindow;

namespace Ui {
class Hs_analyse;
}

class Hs_analyse : public QWidget
{
    Q_OBJECT

public:
    explicit Hs_analyse(QWidget *parent = nullptr);
    ~Hs_analyse();

    void connect_to_server();
    void node_select();
    void node_setting();
    void create_analyse();
    void update_data();
    void test1();


    QVector<hs_node*>   get_m_nodes();
    Hs_OpcUAClient*     get_m_client();

signals:
    //void create_analyse();
    //void update_data();

private slots:
    //接受来自Hs_connect_to_server类的服务器
    void receive_client(Hs_OpcUAClient*);
    void test2();

private:
    Ui::Hs_analyse          *ui;
    QVector<hs_node*>       m_nodes;
    Hs_connect_to_server    *m_connect_to_server=nullptr;
    Hs_collect_setting      *m_node_select=nullptr;
    Hs_Node_setting         *m_node_setting=nullptr;
    Hs_OpcUAClient          *m_client=nullptr;
    MainWindow              *m_parent=nullptr;
    QMap<QOpcUaNode*,int>   m_map;
    int                     index=0;

//周期计数节点
    QOpcUaNode              *m_shotcountNode;
//测试节点
    QOpcUaNode              *testnode;
    QOpcUaNode              *testnode2;
    MyThread                *newthread=nullptr;

};

#endif // HS_ANALYSE_H
