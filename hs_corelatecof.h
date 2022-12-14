#ifndef HS_CORELATECOF_H
#define HS_CORELATECOF_H

#include <QWidget>
#include <QLineEdit>
#include <QSpacerItem>
#include <QMenu>
#include <math.h>
#include <QTableWidget>
#include "hs_corelatecoefmodel.h"
#include "hs_node.h"

class Hs_analyse;

namespace Ui {
class Hs_CorelateCOF;
}

class Hs_CorelateCOF : public QWidget
{
    Q_OBJECT

public:
    explicit Hs_CorelateCOF(QVector<hs_node*>&nodes,QTableWidget *table,QWidget *parent = nullptr);
    ~Hs_CorelateCOF();

    static double cal_COEF(QVector<double>&data1,QVector<double>&data2);

    void add_display_part();//添加相关系数展示框

    void update_combobox();

private slots:
    void SLOT_update_COEF(int);

    void on_pushButton_clicked();

    void on_Hs_CorelateCOF_customContextMenuRequested(const QPoint &pos);

    void on_actHideWindow_triggered();

private:
    Ui::Hs_CorelateCOF *ui;
    QSpacerItem                     *spacer_item = nullptr;
    QVector<Hs_CoRelateCOEFModel*>  m_models;
    QVector<hs_node*>               *m_nodes;
    QTableWidget                    *m_table;
    QVector<double>                 m_data_series_A;
    QVector<double>                 m_data_series_B;
    Hs_analyse                      *m_parent=nullptr;
};

#endif // HS_CORELATECOF_H
