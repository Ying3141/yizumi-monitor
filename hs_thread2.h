#ifndef HS_THREAD2_H
#define HS_THREAD2_H
#include<QThread>
#include<QDebug>
#include<QtOpcUa>

//测试用线程，暂未使用
class MainWindow;

class MyThread_2 : public QThread
{
    Q_OBJECT
public:
    MyThread_2(QOpcUaNode *node,QObject* parent = nullptr);
    //自定义发送的信号
protected:
    void run() override;
private:
    QOpcUaNode *m_node;
    MainWindow *m_parent;
};

#endif // MYTHREAD_H
