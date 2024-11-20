#include <QApplication>
#include "mainwindow.h"

int main(int argc, char** argv)
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}

//Дописать модель
//реализовать функции добавления вектора, изменения, удаления из модели, превью
