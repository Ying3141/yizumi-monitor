#ifndef HS_COLLECT_SETTING_H
#define HS_COLLECT_SETTING_H

#include <QWidget>
#include <QLayout>
#include "hs_opcuaclient.h"
#include "hs_node.h"

//节点添加类，输入节点中文意义和node名，添加节点到Hs_node节点类。自定义信号为发送当前创建的服务器，
namespace Ui {
class Hs_collect_setting;
}

class Hs_collect_setting : public QWidget
{
    Q_OBJECT

public:
    explicit Hs_collect_setting(QVector<hs_node*>&m_nodes,QWidget *parent = nullptr);
    ~Hs_collect_setting();
    void initialize();

private slots:
    void on_pushButton_clicked();

private:
    Ui::Hs_collect_setting *ui;
    QVector<hs_node*>   *m_nodes;
    QGridLayout         *m_GridLayout;
};

#endif // HS_COLLECT_SETTING_H
