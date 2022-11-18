#ifndef HSMONITORING_H
#define HSMONITORING_H

#include <QWidget>
#include<QDateTime>
#include<QTimer>
#include <QtOpcUa>

class HsConnectConfig;
class HsNodeConfig;
class HsMonitorConfig;

struct statistic_data
{
    double max=double(INT_MIN);
    double min=double(INT_MAX);
    double average=0.0;
    double variance=0.0;
    double coef=0.0;
};

namespace Ui {
class HsMonitoring;
}

class HsMonitoring : public QWidget
{
    Q_OBJECT

public:
    explicit HsMonitoring(QWidget *parent = nullptr);
    ~HsMonitoring();

protected:
    virtual void showEvent(QShowEvent *event);

private:
    void initializeView();
    void initialize_slots();

private slots:
    void time_out();

    void loadModelData();

    void updateModelData();

    void on_pushButton_toggled(bool checked);

    void on_new_mold_detected();

    void on_readAttribute_triggered();

    void on_pushButton_2_clicked();

signals:
    void send_statistic_data(std::vector<statistic_data>);
    void send_newmold_signal();

private:
    Ui::HsMonitoring *ui;

    HsConnectConfig *m_connectConfig = nullptr;
    HsNodeConfig *m_dataNode = nullptr;
    HsMonitorConfig *m_monitorConfig = nullptr;

    QTimer *t_time=nullptr;

    std::vector<QOpcUaNode*>m_OpcUaNode;
    std::vector<statistic_data>m_statisticData;
};

#endif // HSMONITORING_H
