#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QListView>
#include <QComboBox>
#include <QPushButton>
#include <QStringListModel>
#include <QDialog>
#include <QLabel>
#include <QItemSelection>
#include <QLayout>
#include <QHBoxLayout>
#include <QFileDialog>
#include <QFile>
#include <QTextStream>
#include "interpreter.h"
#include "Parser.h"
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

    void handleSelection_VectorView(const QItemSelection&);

    void on_SaveBtn_released();

    void on_OpenBtn_released();

private:
    Ui::MainWindow *ui;
    QListView * VectorView;
    VectorListModel * VecModel;


};

#endif // MAINWINDOW_H
