#include "mainwindow.h"
#include "mvcmainwindow.h"
#include <QApplication>
#include <QMessageBox>
#include <QPushButton>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // Диалог выбора лабораторной работы
    QMessageBox choiceBox;
    choiceBox.setWindowTitle("Выбор лабораторной работы");
    choiceBox.setText("Какую часть лабораторной работы запустить?");

    QPushButton *part1Button = choiceBox.addButton("Часть 1 - Круги", QMessageBox::ActionRole);
    QPushButton *part2Button = choiceBox.addButton("Часть 2 - MVC", QMessageBox::ActionRole);
    QPushButton *cancelButton = choiceBox.addButton("Отмена", QMessageBox::RejectRole);

    choiceBox.exec();

    if (choiceBox.clickedButton() == part1Button) {
        // Запуск части с кругами
        MainWindow w;
        w.show();
        return a.exec();
    } else if (choiceBox.clickedButton() == part2Button) {
        // Запуск части с MVC
        MVCMainWindow w;
        w.show();
        return a.exec();
    }

    return 0;
}
