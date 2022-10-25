#ifndef HSCONNECTCONFIG_H
#define HSCONNECTCONFIG_H

#include <QWidget>
#include <QtOpcUa>

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

    QOpcUaClient*   get_m_opcClient();
    QOpcUaNode*     get_m_shotcountNode();

private slots:
    void on_connect_clicked();

    void on_endpointsRequestFinished (QVector<QOpcUa::QEndpointDescription> endpoints , QOpcUa::UaStatusCode statusCode);

    void on_stateChanged(QOpcUaClient::ClientState state);

private:
    void initializeView();

private:
    Ui::HsConnectConfig *ui;

    QOpcUaProvider *m_opcPrivider = nullptr;
    QOpcUaClient *m_opcClient = nullptr;
    QOpcUaNode *m_shotcountNode = nullptr;

};

#endif // HSCONNECTCONFIG_H
