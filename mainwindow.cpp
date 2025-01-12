#include "mainwindow.h"
#include "ui_mainwindow.h"

void MainWindow::errDlg(QString text)
{
    QDialog *errDlg = new QDialog(this);
    errDlg->setWindowTitle("Error");

    errDlg->setSizeGripEnabled(false);

    QHBoxLayout * layout = new QHBoxLayout(errDlg);

    QLabel *errTxt = new QLabel(text);

    layout->addWidget(errTxt);

    errDlg->setMinimumSize(350, 50);
    errDlg->setMaximumSize(350, 50);

    errTxt->setFont(QFont("Helvetica", 14, QFont::Thin, false));
    errTxt->setAlignment(Qt::AlignCenter);
    errTxt->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);

    errDlg->exec();

    delete errTxt;
    delete errDlg;

    return;
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    setWindowFlags(Qt::Window | Qt::CustomizeWindowHint | Qt::WindowTitleHint
                   | Qt::WindowCloseButtonHint | Qt::WindowMinimizeButtonHint);

    ui->SaveChangesBtn->setEnabled(false);
    ui->VectorPreview->setEnabled(false);
    ui->RemoveBtn->setEnabled(false);

    VecModel = new VectorListModel();

    ui->VectorView->setModel(VecModel);
    ui->OperandBox->setModel(VecModel);

    connect(ui->VectorView->selectionModel(),
            SIGNAL(selectionChanged(QItemSelection, QItemSelection)),
            this,
            SLOT(handleSelection_VectorView(QItemSelection)));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_VectorView_clicked(const QModelIndex &index)
{
    VecLib::Vector vec = (index.data(VectorListModel::VectorRole))
                             .value<VecLib::Vector>();

    QString charString = tr(vec.getName().c_str()) + tr(" [")
                         + tr(std::to_string(vec.size()).c_str()) + tr("] (");

    ul j = 0;
    for (ul i = 0; i < vec.size(); i++) {
        charString += tr(vec.at_s(i).c_str());
        if (j < vec.size() - 1) {
            charString += tr(", ");
            j++;
        }
    }

    charString += tr(")");

    ui->SaveChangesBtn->setEnabled(true);
    ui->VectorPreview->setEnabled(true);
    ui->RemoveBtn->setEnabled(true);
    ui->VectorPreview->setText(charString);
}

void MainWindow::on_AddBtn_released()
{
    VecModel->insertRows(0, 1);
}

void MainWindow::on_RemoveBtn_released()
{
    QModelIndexList indices = ui->VectorView->selectionModel()->selectedIndexes();
    if (indices.size() == 0)
        return;
    for (auto i : indices)
        VecModel->removeRows(i.row(), 1);

    ui->VectorView->clearSelection();
}

void MainWindow::on_SaveChangesBtn_released()
{
    QString qstr = ui->VectorPreview->text();
    std::string str = qstr.toUtf8().data();
    try {
        VecLib::Vector vec = VectorParser::Parse(VectorLexer::Tokenize(str)).at(0);
        QModelIndex selected = ui->VectorView->selectionModel()->selectedIndexes()[0];
        VecModel->setData(selected, QVariant::fromValue(vec), VectorListModel::VectorRole);
    } catch (...) {
        errDlg("Bad vector");
    }
}

void MainWindow::handleSelection_VectorView(const QItemSelection &selection)
{
    if (selection.indexes().isEmpty()) {
        ui->SaveChangesBtn->setEnabled(false);
        ui->VectorPreview->setText(tr(""));
        ui->VectorPreview->setEnabled(false);
        ui->RemoveBtn->setEnabled(false);
    } else {
        ui->SaveChangesBtn->setEnabled(true);
        ui->VectorPreview->setEnabled(true);
        ui->RemoveBtn->setEnabled(true);
    }
}

void MainWindow::on_VectorView_activated(const QModelIndex &index) {}

void MainWindow::on_SaveBtn_released()
{
    QString fileName = QFileDialog::getSaveFileName(this,
                                                    tr("Save config"),
                                                    tr("C:\\"),
                                                    tr("Text files (*.txt)"));

    if (fileName.size() == 0)
        return;

    QString config = VecModel->formConfig();

    QFile fileToSave(fileName);

    if (!fileToSave.open(QIODevice::WriteOnly | QIODevice::Text)) {
        errDlg("unable to find location");
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

    if (fileName.size() == 0)
        return;

    QFile file(fileName);

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        errDlg("unable to find location");
    }

    QList<VecLib::Vector> updatedList;

    QTextStream in(&file);
    try {
        while (!in.atEnd()) {
            QString line = in.readLine();
            std::string stdStr = line.toUtf8().data();

            if (stdStr.empty())
                break;
            updatedList.append(Parse(VectorLexer::Tokenize(stdStr))[0]);
        }
    }
    catch (const char *) {
        errDlg("config malformed");

        return;
    }

    VecModel->removeRows(0, VecModel->rowCount());

    VecModel->insertRows(0, updatedList.size());

    for (int i = 0; i < updatedList.size(); i++)
        VecModel->setData(VecModel->index(i),
                          QVariant::fromValue(updatedList.at(i)),
                          VectorListModel::VectorRole);
}

void MainWindow::on_SolveBtn_released()
{
    QString Qexpr = ui->SentanceField->toPlainText();
    std::string expr = Qexpr.toStdString();

    try {
        CalcTools::Tokens toks = CalcTools::Tokenize(expr.c_str());
        if (!CalcTools::CheckPars(toks)) {ui->ResultField->setText("invalid syntax"); return;}
        CalcTools::Tokens RPN = CalcTools::Parse(toks);
        CalcTools::Token result = CalcTools::Calculator(RPN, VecModel);

        QString formedResult = "";

        if (result.type() == IntTokenType::VECOBJ)
        {
            VecLib::Vector resVec = (VecLib::Vector)result;
            formedResult = tr("result") + tr(" ") +
                           tr("[") + tr(std::to_string(resVec.size()).c_str()) + tr("](");
            int size = resVec.size();
            for (int i = 0; i < size; i++)
            {
                formedResult += tr(std::to_string(resVec.at(i)).c_str());
                if (i < size - 1) formedResult += tr(", ");
            }
            formedResult += tr(")\n");
        }
        else if (result.type() == IntTokenType::NUM)
        {
            formedResult += tr(std::to_string((e_type)result).c_str());
        }
        else
            formedResult += tr("bad expression");


        ui->ResultField->setText(formedResult);
    }
    catch(const char* e)
    {
        errDlg(e);
    }
    catch(...)
    {
        ui->ResultField->setText("unknown exception");
    }
}


void MainWindow::on_SaveResultBtn_released()
{
    QString line = ui->ResultField->toPlainText();
    if (line.size() == 0)
    {
        errDlg("empty line");
        return;
    }

    VecLib::Vector a;

    try {
        a = VectorParser::Parse(VectorLexer::Tokenize(line.toStdString()))[0];
        VecModel->insertRows(0, 1);
        VecModel->setData(VecModel->index(0),
                          QVariant::fromValue(a),
                          VectorListModel::VectorRole);
    }
    catch (...)
    {
        errDlg("nothing to save");
    }
}

void MainWindow::on_MaxIndexesBtn_released()
{
    VecLib::Vector curr = ui->
                          OperandBox->
                          currentData(VectorListModel::VectorRole)
                              .value<VecLib::Vector>();
    std::vector<ul> result = curr.maxsIndices();

    QString resLine = "Max value: ";
    resLine += curr.at_s(result.at(0));
    resLine += "\nIndecies: ";
    ul commas = 0;
    for (auto& i : result)
    {
        resLine += std::to_string(i).c_str();
        if (commas < result.size() - 1) resLine += ", ";
    }

    ui->ResultLine->setText(resLine);
}


void MainWindow::on_MinIndexesBtn_released()
{
    VecLib::Vector curr = ui->
                          OperandBox->
                          currentData(VectorListModel::VectorRole)
                              .value<VecLib::Vector>();
    std::vector<ul> result = curr.minsIndices();

    QString resLine = "Min value: ";
    resLine += curr.at_s(result.at(0));
    resLine += "\nIndecies: ";
    ul commas = 0;
    for (auto& i : result)
    {
        resLine += std::to_string(i).c_str();
        if (commas < result.size() - 1) resLine += ", ";
        commas++;
    }

    ui->ResultLine->setText(resLine);
}


void MainWindow::on_pushButton_released()
{
    OpInfo(this).exec();
}

