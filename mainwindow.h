#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLayout>
#include <QTableWidget>
#include <QtOpcUa>
#include "hs_analyse.h"
#include "hs_analyse_action.h"


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    Ui::MainWindow      *ui;
    QHBoxLayout         *m_DownLay;
    QTableWidget        *m_table=nullptr;
    Hs_analyse          *analyse=nullptr;

    //初始化TabWidget，
    //初始化动作类hs_analyse_action
    //初始化动作实现类hs_analyse
    //目前所有功能放在Hs_analyse模块下

    void initializeTab();
    void initializeUI();
    void initslots();

private slots:

//    void on_create_analyse();
//    void on_update_data();
    void set_statusbartext(QString);

private:
//    Ui::MainWindow      *ui;
//    QHBoxLayout         *m_DownLay;
//    QTableWidget        *m_table=nullptr;
//    Hs_analyse          *analyse=nullptr;
    QTabWidget          *m_TabWidget;
    QGridLayout         *m_mainVLay;
    QHBoxLayout         *m_UpLay;


    Hs_Analyse_Action *analyse_action=nullptr;

};

#endif // MAINWINDOW_H
