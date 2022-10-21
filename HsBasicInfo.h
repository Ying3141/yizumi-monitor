#ifndef HSBASICINFO_H
#define HSBASICINFO_H

#include <QWidget>

namespace Ui {
class HsBasicInfo;
}

class HsBasicInfo : public QWidget
{
    Q_OBJECT

public:
    explicit HsBasicInfo(QWidget *parent = nullptr);
    ~HsBasicInfo();

private:
    Ui::HsBasicInfo *ui;
};

#endif // HSBASICINFO_H
