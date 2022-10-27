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

private:
    Ui::HsMonitoring *ui;

    HsConnectConfig *m_connectConfig = nullptr;
    HsNodeConfig *m_dataNode = nullptr;
    HsMonitorConfig *m_monitorConfig = nullptr;

    QTimer *t_time=nullptr;
};

#endif // HSMONITORING_H
