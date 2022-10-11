#ifndef HS_NODE_SETTING_H
#define HS_NODE_SETTING_H

#include <QWidget>
#include "hs_node.h"

//节点设置类，设置和查看不同节点的上下限。
namespace Ui {
class Hs_Node_setting;
}

class Hs_Node_setting : public QWidget
{
    Q_OBJECT

public:
    explicit Hs_Node_setting(QVector<hs_node*>&m_nodes,QWidget *parent = nullptr);
    ~Hs_Node_setting();
    void initialize();

private slots:
    void on_nodename_comboBox_currentIndexChanged(int index);

    void on_uplimit_doubleSpinBox_valueChanged(double arg1);

    void on_downlimit_doubleSpinBox_valueChanged(double arg1);

private:


private:
    Ui::Hs_Node_setting *ui;
    QVector<hs_node*>   *m_nodes;
};

#endif // HS_NODE_SETTING_H
