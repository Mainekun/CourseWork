#ifndef OPINFO_H
#define OPINFO_H

#include <QDialog>

namespace Ui {
class OpInfo;
}

class OpInfo : public QDialog
{
    Q_OBJECT

public:
    explicit OpInfo(QWidget *parent = nullptr);
    ~OpInfo();

private:
    Ui::OpInfo *ui;
};

#endif // OPINFO_H
