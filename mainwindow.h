#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLayout>
#include <QTableWidget>
#include <QtOpcUa>
#include <QMenu>
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

//开放主界面UI权限，使子界面可以进行调用
    Ui::MainWindow      *ui;
    QHBoxLayout         *m_DownLeftLay=nullptr;
    QHBoxLayout         *m_DownRightLay=nullptr;
    Hs_analyse          *analyse=nullptr;
    QTabWidget          *m_TabWidget;
    QGridLayout         *m_mainGLay;
    QHBoxLayout         *m_UpLay;

    //初始化TabWidget，
    //初始化动作类hs_analyse_action
    //初始化动作实现类hs_analyse
    //目前所有功能放在Hs_analyse模块下

    void initializeTab();
    void initializeUI();
    void initslots();

private slots:
    void set_statusbartext(QString);
    void hidewindow();
    void on_actHideTab_triggered();
    void on_tabWidget_customContextMenuRequested(const QPoint &pos);

private:

    bool                b_hidebar=false;
    Hs_Analyse_Action   *analyse_action=nullptr;

};

#endif // MAINWINDOW_H
