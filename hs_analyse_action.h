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
    void bindWidget(QWidget *widget);
    void initialize();

private:
    void initialize_slots();

private:
    Ui::Hs_Analyse_Action *ui;

    Hs_analyse *m_analyse=nullptr;

private slots:
    void on_connect_to_server_clicked();
    void on_node_setting_clicked();
    void on_create_analyse_clicked();
    void on_update_data_clicked();
    void on_test1_clicked();
    void on_test2_clicked();

};

#endif // HS_ANALYSE_ACTION_H
