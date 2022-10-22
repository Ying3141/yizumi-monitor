#ifndef HSMONITORCONFIG_H
#define HSMONITORCONFIG_H

#include <QWidget>

namespace Ui {
class HsMonitorConfig;
}

class HsMonitorConfig : public QWidget
{
    Q_OBJECT

public:
    explicit HsMonitorConfig(QWidget *parent = nullptr);
    ~HsMonitorConfig();

private:
    void initializeView();

private:
    Ui::HsMonitorConfig *ui;
};

#endif // HSMONITORCONFIG_H
