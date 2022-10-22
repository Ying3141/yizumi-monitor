#ifndef HSMONITORING_H
#define HSMONITORING_H

#include <QWidget>

class HsConnectConfig;
class HsNodeConfig;
class HsMonitorConfig;

namespace Ui {
class HsMonitoring;
}

class HsMonitoring : public QWidget
{
    Q_OBJECT

public:
    explicit HsMonitoring(QWidget *parent = nullptr);
    ~HsMonitoring();

private:
    void initializeView();

private:
    Ui::HsMonitoring *ui;

    HsConnectConfig *m_connectConfig = nullptr;
    HsNodeConfig *m_dataNode = nullptr;
    HsMonitorConfig *m_monitorConfig = nullptr;
};

#endif // HSMONITORING_H
