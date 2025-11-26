#include "mainwindow.h"
#include <QApplication>
#include <QDebug>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // Настройка приложения
    a.setApplicationName("Визуальный редактор");
    a.setApplicationVersion("1.0");
    a.setOrganizationName("ООП Лабораторная работа 4");

    MainWindow w;
    w.show();

    return a.exec();
}
