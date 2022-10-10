#ifndef HS_ANALYSE_H
#define HS_ANALYSE_H

#include <QWidget>
#include <QTableWidget>
#include "hs_connect_to_server.h"
#include "hs_collect_setting.h"

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
    void collect_setting();
    //void create_analyse();
    //void update_data();
    void test1();
    void test2();

    QVector<hs_node*>   get_m_nodes();
    Hs_OpcUAClient*     get_m_client();

signals:
    void create_analyse();
    void update_data();

private slots:
    void receive_client(Hs_OpcUAClient*);

private:
    Ui::Hs_analyse          *ui;
    QVector<hs_node*>       m_nodes;
    Hs_connect_to_server    *m_connect_to_server=nullptr;
    Hs_collect_setting      *m_collect_setting=nullptr;
    Hs_OpcUAClient          *m_client=nullptr;
    MainWindow              *m_parent=nullptr;


};

#endif // HS_ANALYSE_H
