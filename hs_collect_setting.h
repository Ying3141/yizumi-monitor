#ifndef HS_COLLECT_SETTING_H
#define HS_COLLECT_SETTING_H

#include <QWidget>
#include <QLayout>
#include "hs_opcuaclient.h"
#include "hs_node.h"
#include <QCloseEvent>

//节点添加类，输入节点中文意义和node名，添加节点到Hs_node节点类。
namespace Ui {
class Hs_collect_setting;
}

class Hs_collect_setting : public QWidget
{
    Q_OBJECT

public:
    explicit Hs_collect_setting(Hs_OpcUAClient*,QVector<hs_node*>&m_nodes,QWidget *parent = nullptr);
    ~Hs_collect_setting();
    void initialize();

protected :
    void closeEvent(QCloseEvent *event);

private slots:
    void on_pushButton_clicked();

signals:
    void ui_closed();

private:
    Ui::Hs_collect_setting *ui;
    QVector<hs_node*>   *m_nodes;
    QGridLayout         *m_GridLayout;
    Hs_OpcUAClient      *m_client;
};

#endif // HS_COLLECT_SETTING_H
