#ifndef HSANALYSIS_H
#define HSANALYSIS_H

#include <QWidget>
#include "HsMonitoring.h"
#include "HsQualityConfig.h"

namespace Ui {
class HsAnalysis;
}

class HsAnalysis : public QWidget
{
    Q_OBJECT

public:
    explicit HsAnalysis(QWidget *parent = nullptr);
    ~HsAnalysis();

public slots:
    void on_statistic_data_receive(std::vector<statistic_data>);

    void on_newMold_signal_receive();

private slots:
    void on_pushButton_clicked();

private:
    void initializeView();

    void loadModelData();

    void updateModelData();

    void initialize_slots();

    void update_table(std::vector<statistic_data>);

    float cal_coef(QList<float>,QList<float>);

private:
    Ui::HsAnalysis *ui;

    HsQualityConfig *m_qualityConfig = nullptr;
};

#endif // HSANALYSIS_H
