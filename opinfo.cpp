#include "opinfo.h"
#include "ui_opinfo.h"

OpInfo::OpInfo(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::OpInfo)
{
    ui->setupUi(this);
}

OpInfo::~OpInfo()
{
    delete ui;
}
