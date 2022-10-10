#ifndef HS_NODE_SETTING_H
#define HS_NODE_SETTING_H

#include <QWidget>
#include "hs_node.h"

namespace Ui {
class Hs_Node_setting;
}

class Hs_Node_setting : public QWidget
{
    Q_OBJECT

public:
    explicit Hs_Node_setting(QVector<hs_node*>&m_nodes,QWidget *parent = nullptr);
    ~Hs_Node_setting();

private slots:
    void on_nodename_comboBox_currentIndexChanged(int index);

    void on_uplimit_doubleSpinBox_valueChanged(double arg1);

    void on_downlimit_doubleSpinBox_valueChanged(double arg1);

private:
    void initialize();

private:
    Ui::Hs_Node_setting *ui;
    QVector<hs_node*>   *m_nodes;
};

#endif // HS_NODE_SETTING_H
