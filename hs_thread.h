#ifndef MYTHREAD_H
#define MYTHREAD_H
#include<QThread>
#include<QDebug>
#include<QtOpcUa>

//测试用线程，暂未使用
class MyThread : public QThread
{
    Q_OBJECT
public:
    MyThread(QOpcUaNode *node,QObject* parent = nullptr);
    //自定义发送的信号
protected:
    void run() override;
private:
    QOpcUaNode *m_node;
};

#endif // MYTHREAD_H

