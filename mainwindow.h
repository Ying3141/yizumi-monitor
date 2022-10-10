#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QLayout>
#include <QTableWidget>
#include <QSpacerItem>
#include <QtOpcUa>
#include <windows.h>
#include "hs_connect_to_server.h"
#include "hs_analyse.h"
#include "hs_opcuaclient.h"
#include "hs_node.h"
#include "hs_collect_setting.h"
#include "hs_thread.h"
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
