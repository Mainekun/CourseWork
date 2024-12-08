#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QComboBox>
#include <QDialog>
#include <QFile>
#include <QFileDialog>
#include <QHBoxLayout>
#include <QItemSelection>
#include <QLabel>
#include <QLayout>
#include <QListView>
#include <QMainWindow>
#include <QPushButton>
#include <QStringList>
#include <QStringListModel>
#include <QTextStream>
#include "Parser.h"
#include "interpreter.h"
#include "vectorlistmodel.h"

using namespace VectorParser;
using namespace VectorLexer;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_VectorView_clicked(const QModelIndex &index);

    void on_AddBtn_released();

    void on_RemoveBtn_released();

    void on_SaveChangesBtn_released();

    void on_VectorView_activated(const QModelIndex &index);

    void handleSelection_VectorView(const QItemSelection &);

    void on_SaveBtn_released();

    void on_OpenBtn_released();

    void on_SolveBtn_released();

    void on_SaveResultBtn_released();

    void on_MaxIndexesBtn_released();

    void on_MinIndexesBtn_released();

private:
    Ui::MainWindow *ui;
    QListView *VectorView;
    VectorListModel *VecModel;

    void errDlg(QString);
};

#endif // MAINWINDOW_H
