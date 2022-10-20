#ifndef HS_ANALYSE_H
#define HS_ANALYSE_H

#include <QWidget>
#include <QTableWidget>
#include "hs_database.h"
#include "hs_connect_to_server.h"
#include "hs_collect_setting.h"
#include "hs_corelatecof.h"
#include "hs_historydata.h"
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
    MainWindow              *m_parent=nullptr;
    QHBoxLayout             *m_DownRightLay;

public:
    explicit Hs_analyse(QWidget *parent = nullptr);
    ~Hs_analyse();
    void connect_to_server();
    void node_select();
    void node_setting();
    void create_analyse();
    void start_collecting();
    void stop_collecting();
    void write_test();
    void create_database_table();
    void create_cov_window();
    void create_historydata_window();
    void test1();
    void test2();

    QVector<hs_node*>       get_m_nodes();
    Hs_OpcUAClient*         get_m_client();
    Hs_connect_to_server*   get_m_connect_to_server();

private slots:
    //接受来自Hs_connect_to_server类的服务器
    void receive_client(Hs_OpcUAClient*);
    void write_to_table();
    void on_new_mold_detected();

private:
    Ui::Hs_analyse          *ui;
    QVector<hs_node*>       m_nodes;
    Hs_connect_to_server    *m_connect_to_server=nullptr;
    Hs_collect_setting      *m_node_select=nullptr;
    Hs_OpcUAClient          *m_client=nullptr;
    QMap<QOpcUaNode*,int>   m_map;
    int                     index=0;
    bool                    is_first_mold=true;
    QTableWidget            *m_table=nullptr;
//相关分析窗口
    Hs_CorelateCOF          *m_coef=nullptr;
//当前数据库工作表格名
    QString                 m_cur_active_DBTable;
//周期计数节点
    QOpcUaNode              *m_shotcountNode=nullptr;
//SQLite数据库
    Hs_Database             *m_DB=nullptr;
//测试节点
    QOpcUaNode              *testnode=nullptr;
//历史数据查看窗口
    Hs_HistoryData          *m_history=nullptr;

};

#endif // HS_ANALYSE_H
