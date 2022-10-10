#ifndef HS_COLLECT_SETTING_H
#define HS_COLLECT_SETTING_H

#include <QWidget>
#include <QLayout>
#include "hs_opcuaclient.h"
#include "hs_node.h"

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
