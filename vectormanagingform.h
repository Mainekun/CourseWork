#ifndef VECTORMANAGINGFORM_H
#define VECTORMANAGINGFORM_H

#include <QWidget>
#include "vectoreditdialog.h"
#include "vectorinputdialog.h"
#include "vectorlistmodel.h"

namespace Ui {
class VectorManagingForm;
}

class VectorManagingForm : public QWidget
{
    Q_OBJECT

public:
    explicit VectorManagingForm(QWidget *parent = nullptr);
    ~VectorManagingForm();

private slots:
    void on_AddBtn_released();

    void on_EditBtn_released();

private:
    Ui::VectorManagingForm *ui;
    VectorListModel *VecModel;
};

#endif // VECTORMANAGINGFORM_H
