#ifndef HS_ANALYSE_ACTION_H
#define HS_ANALYSE_ACTION_H

#include <QWidget>
#include "hs_analyse.h"

namespace Ui {
class Hs_Analyse_Action;
}

class Hs_Analyse_Action : public QWidget
{
    Q_OBJECT

public:
    explicit Hs_Analyse_Action(QWidget *parent = nullptr);
    ~Hs_Analyse_Action();

public:
    //动作类与实现类绑定函数
    void bindWidget(QWidget *widget);

private:
    void initialize_slots();
    void initialize();

private:
    Ui::Hs_Analyse_Action *ui;

    Hs_analyse *m_analyse=nullptr;

private slots:
    //按键功能绑定
    void on_connect_to_server_clicked();
    void on_node_select_clicked();
    void on_node_setting_clicked();
    void on_create_analyse_clicked();
    void on_test1_clicked();
    void on_test2_clicked();
    void on_start_collecting_toggled(bool checked);
    void on_cov_analyse_clicked();
};

#endif // HS_ANALYSE_ACTION_H
