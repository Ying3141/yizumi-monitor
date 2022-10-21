#ifndef HSHOMEPAGE_H
#define HSHOMEPAGE_H

#include <QWidget>

namespace Ui {
class HsHomePage;
}

class HsHomePage : public QWidget
{
    Q_OBJECT

public:
    explicit HsHomePage(QWidget *parent = nullptr);
    ~HsHomePage();

private:
    Ui::HsHomePage *ui;
};

#endif // HSHOMEPAGE_H
