#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLayout>
#include <QTableWidget>
#include <QtOpcUa>
#include <QMenu>
#include "hs_analyse.h"
#include "hs_analyse_action.h"

class HsMainWindow;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    friend class HsMainWindow;

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

public:
    static QMap<QString, QAction *> &getActionMap() {
        return m_actionMap;
    }

private:
    void initializeView();
    void updateToolBar(int viewType);

private slots:
    void hidewindow();

    void on_actHideTab_triggered();

    void on_tabWidget_customContextMenuRequested(const QPoint &pos);

    void on_actNodeSetting_triggered();

    void on_actNewMachine_triggered();

    void on_actHistoryData_triggered();

private:

    bool                b_hidebar=false;
    Hs_Analyse_Action   *analyse_action=nullptr;

    static QMap<QString, QAction *> m_actionMap;
    QToolBar *m_toolBar = nullptr;
    HsMainWindow *m_hsMainWindow = nullptr;
    QHash<int, QStringList> m_toolbarMap;
};

#endif // MAINWINDOW_H
