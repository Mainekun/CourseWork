#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    setWindowFlags(Qt::Window | Qt::CustomizeWindowHint |
                   Qt::WindowTitleHint | Qt::WindowCloseButtonHint |
                   Qt::WindowMinimizeButtonHint);

    ui->SaveChangesBtn->setEnabled(false);
    ui->VectorPreview->setEnabled(false);

    VecModel = new VectorListModel();


    ui->VectorView->setModel(VecModel);
    ui->OperandBox->setModel(VecModel);

    connect(ui->VectorView->selectionModel(), SIGNAL(selectionChanged(QItemSelection,QItemSelection)),
            this, SLOT(handleSelection_VectorView(QItemSelection)));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_VectorView_clicked(const QModelIndex &index)
{
    Vector vec = (index.data(VectorListModel::VectorRole)).value<Vector>();
    QString charString = tr(vec.getName().c_str()) + tr(" [")
                         + tr(std::to_string(vec.size()).c_str()) + tr("] (");

    int j = 0;
    for (auto i : vec)
    {
        charString += tr(dtos(i, 2).c_str());
        if(j < vec.size() - 1)
        {
            charString += tr(", ");
            j++;
        }
    }

    charString += tr(")");

    ui->SaveChangesBtn->setEnabled(true);
    ui->VectorPreview->setEnabled(true);
    ui->VectorPreview->setText(charString);
}


void MainWindow::on_AddBtn_released()
{
    VecModel->insertRows(0, 1);
}


void MainWindow::on_RemoveBtn_released()
{
    QModelIndexList indices = ui->VectorView->selectionModel()->selectedIndexes();
    if (indices.size() == 0) return;
    for (auto i : indices)
        VecModel->removeRows(i.row(), 1);

    ui->VectorView->clearSelection();
}


void MainWindow::on_SaveChangesBtn_released()
{
    QString qstr = ui->VectorPreview->text();
    std::string str = qstr.toUtf8().data();
    try {
        Vector vec = VectorParser::Parse(VectorLexer::Tokenize(str)).at(0);
        QModelIndex selected = ui->VectorView->selectionModel()->selectedIndexes()[0];
        VecModel->setData(selected, QVariant::fromValue(vec), VectorListModel::VectorRole);
    }
    catch (...)
    {
        QDialog * dlg = new QDialog(this);
        dlg->setFixedSize(140, 40);

        QHBoxLayout * hlayout = new QHBoxLayout(dlg);

        QLabel *text = new QLabel(tr("bad vector"));
        hlayout->addWidget(text);
        text->setFont(QFont(tr("Comic Sans MS"), 14, QFont::Thin, false));

        //text->setAlignment(Qt::AlignCenter);

        dlg->exec();
    }

}

void MainWindow::handleSelection_VectorView(const QItemSelection& selection)
{
    if (selection.indexes().isEmpty())
    {
        ui->SaveChangesBtn->setEnabled(false);
        ui->VectorPreview->setText(tr(""));
        ui->VectorPreview->setEnabled(false);
    }
    else
    {
        ui->SaveChangesBtn->setEnabled(true);
        ui->VectorPreview->setEnabled(true);
    }
}

void MainWindow::on_VectorView_activated(const QModelIndex &index)
{

}


void MainWindow::on_SaveBtn_released()
{
    QString fileName = QFileDialog::getSaveFileName(this,
        tr("Save config"),
        tr("C:\\"),
        tr("Text files (*.txt)"));

    if (fileName.size() == 0) return;

    QString config = VecModel->formConfig();

    QFile fileToSave(fileName);

    if (!fileToSave.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        QDialog *errDlg = new QDialog(this);
        errDlg->setWindowTitle(tr("Error"));

        QLabel *errTxt = new QLabel(tr("unable to find location"), errDlg);

        errDlg->exec();

        delete errTxt;
        delete errDlg;

        return;
    }

    QTextStream out(&fileToSave);

    out << config;

    fileToSave.close();
}


void MainWindow::on_OpenBtn_released()
{   
    QString fileName = QFileDialog::getOpenFileName(this,
                                                    tr("Open config"),
                                                    tr("C:\\"),
                                                    tr("Text files (*.txt)"));

    if (fileName.size()==0) return;

    QFile file(fileName);

    if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QDialog *errDlg = new QDialog(this);
        errDlg->setWindowTitle(tr("Error"));

        QLabel *errTxt = new QLabel(tr("unable to find location"), errDlg);

        errDlg->exec();

        delete errTxt;
        delete errDlg;

        return;
    }

    QList<Vector> updatedList;

    QTextStream in(&file);
    try
    {
        while(!in.atEnd())
        {
            QString line = in.readLine();
            std::string stdStr = line.toUtf8().data();

            if (stdStr.empty()) break;
            updatedList.append(Parse(VectorLexer::Tokenize(stdStr))[0]);
        }
    }
    catch (const char*)
    {
        QDialog *errDlg = new QDialog(this);
        errDlg->setWindowTitle(tr("Error"));

        QLabel *errTxt = new QLabel(tr("config malformed"), errDlg);

        errDlg->exec();

        delete errTxt;
        delete errDlg;

        return;
    }

    VecModel->removeRows(0, VecModel->rowCount());

    VecModel->insertRows(0, updatedList.size());

    for (int i = 0; i < updatedList.size(); i++)
        VecModel->setData(VecModel->index(i),
                          QVariant::fromValue(updatedList.at(i)), VectorListModel::VectorRole);

}

