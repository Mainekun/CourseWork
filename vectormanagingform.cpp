#include "vectormanagingform.h"
#include "ui_vectormanagingform.h"

VectorManagingForm::VectorManagingForm(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::VectorManagingForm)
{
    ui->setupUi(this);

    VecModel = new VectorListModel();

    ui->listView->setModel(VecModel);
}

VectorManagingForm::~VectorManagingForm()
{
    delete ui;
}

void VectorManagingForm::on_AddBtn_released()
{
    VectorInputDialog * Idlg =  new VectorInputDialog(this);
    int status = Idlg->exec();

    if (status == QDialog::Accepted)
        VecModel->addVector(Idlg->getLB());

    delete Idlg;
}

void VectorManagingForm::on_EditBtn_released()
{
    VectorEditDialog * Edlg = new VectorEditDialog(this);
    int status = Edlg->exec();

    if (status == QDialog::Accepted)
        ;

    delete Edlg;
}

