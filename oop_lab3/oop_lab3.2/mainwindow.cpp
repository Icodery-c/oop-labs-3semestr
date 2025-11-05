#include "mvcmainwindow.h"
#include <QVBoxLayout>
#include <QWidget>

MVCMainWindow::MVCMainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    // Создаем модель ПЕРВОЙ
    m_model = new NumberModel(this);
    
    // Создаем представление и передаем ему модель
    m_view = new NumberView(m_model, this);
    
    setCentralWidget(m_view);
    setWindowTitle("Лабораторная работа 3 - MVC");
    resize(400, 300);
}

MVCMainWindow::~MVCMainWindow()
{
}
