#ifndef HSANALYSIS_H
#define HSANALYSIS_H

#include <QWidget>
#include "HsMonitoring.h"

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

private:
    void loadModelData();

    void update_table(std::vector<statistic_data>);

private:
    Ui::HsAnalysis *ui;
};

#endif // HSANALYSIS_H
