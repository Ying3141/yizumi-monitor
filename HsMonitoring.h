#ifndef HSMONITORING_H
#define HSMONITORING_H

#include <QWidget>

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
    Ui::HsMonitoring *ui;
};

#endif // HSMONITORING_H
