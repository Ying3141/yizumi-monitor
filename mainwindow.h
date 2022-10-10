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
#include "hs_thrread.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void initializeConnect();
    void initializeAnalyse();
    void initializeSetting();
    void initializeTab();
    void initializeUI();
    void initslots();

private slots:
    void on_connect_to_server_clicked();
    void on_create_analyse_clicked();
    void on_node_clicked();
    void on_update_data_clicked();
    void on_test2_clicked();
    void set_statusbartext(QString);
    void receive_client(Hs_OpcUAClient*);

private:
    Ui::MainWindow  *ui;
    QTabWidget      *m_TabWidget;
    QPushButton     *m_connect_to_server;
    QPushButton     *m_disconnect_to_server;
    QPushButton     *m_test;
    QPushButton     *m_test2;
    QPushButton     *m_node;
    QPushButton     *m_create_analyse;
    QWidget         *m_connect_setting;
    QWidget         *m_node_setting;
    QWidget         *m_analyse;

    QGridLayout         *m_mainVLay;
    QHBoxLayout         *m_UpLay;
    QHBoxLayout         *m_DownLay;
    Hs_OpcUAClient      *m_client;
    QVector<hs_node*>   m_nodes;
    QTableWidget        *m_table;

    QOpcUaNode *testnode;
};

#endif // MAINWINDOW_H
