#ifndef HSMONITORING_H
#define HSMONITORING_H

#include <QWidget>
#include<QDateTime>
#include<QTimer>

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
    void initialize_slots();

private slots:
    void time_out();

private:
    Ui::HsMonitoring *ui;

    HsConnectConfig *m_connectConfig = nullptr;
    HsNodeConfig *m_dataNode = nullptr;
    HsMonitorConfig *m_monitorConfig = nullptr;

    QTimer *t_time=nullptr;
};

#endif // HSMONITORING_H
