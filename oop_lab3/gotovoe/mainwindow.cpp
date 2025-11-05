#include "mainwindow.h"
//#include "ui_mainwindow.h"
#include <QPainter>

#include <QWheelEvent>

void MainWindow::wheelEvent(QWheelEvent *event)
{
    // Получаем координаты мыши
    int x = event->position().x();
    int y = event->position().y();

    // Проверяем, есть ли круг под курсором
    CCircle* circle = storage.getCircleAt(x, y);
    if (circle) {
        // Определяем направление прокрутки
        int delta = event->angleDelta().y() / 120; // 1 шаг колеса = 120
        double newRadius = circle->getRadius() + delta * 5.0; // шаг 5 пикселей
        if (newRadius < 5) newRadius = 5;       // минимальный размер
        if (newRadius > 200) newRadius = 200;   // максимальный размер
        circle->setRadius(newRadius);
        update();
    }
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    //ui(new Ui::MainWindow)
{
    //ui->setupUi(this);
    setWindowTitle("ЛР3 — Круги на форме");
    setMinimumSize(600, 500);
}

MainWindow::~MainWindow()
{
    //delete ui;
}

void MainWindow::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    storage.drawAll(painter);
}

void MainWindow::mousePressEvent(QMouseEvent *event)
{
    bool ctrlPressed = event->modifiers() & Qt::ControlModifier;
    bool leftClick = event->button() == Qt::LeftButton;

    if (leftClick)
    {
        CCircle *circle = storage.getCircleAt(event->x(), event->y());

        if (circle)
        {
            if (!ctrlPressed)
                storage.deselectAll();
            circle->setSelected(!circle->isSelected());
        }
        else
        {
            if (!ctrlPressed)
                storage.deselectAll();
            storage.add(CCircle(event->x(), event->y()));
        }
        update();
    }
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Delete)
    {
        storage.removeSelected();
        update();
    }
}
