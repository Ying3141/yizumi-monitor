#ifndef HSCONNECTCONFIG_H
#define HSCONNECTCONFIG_H

#include <QWidget>

namespace Ui {
class HsConnectConfig;
}

class QOpcUaProvider;
class QOpcUaClient;
class QOpcUaNode;

class HsConnectConfig : public QWidget
{
    Q_OBJECT

public:
    explicit HsConnectConfig(QWidget *parent = nullptr);
    ~HsConnectConfig();

private slots:
    void on_connect_clicked();

private:
    void initializeView();

private:
    Ui::HsConnectConfig *ui;

    QOpcUaProvider *m_opcPrivider = nullptr;
    QOpcUaClient *m_opcClient = nullptr;
    QOpcUaNode *m_opcNode = nullptr;

};

#endif // HSCONNECTCONFIG_H
