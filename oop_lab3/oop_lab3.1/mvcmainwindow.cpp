#include "mvcmainwindow.h"
#include <QVBoxLayout>
#include <QWidget>

MVCMainWindow::MVCMainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    m_model = new NumberModel(this);
    m_view = new NumberView(m_model, this);

    setCentralWidget(m_view);
    setWindowTitle("Лабораторная работа 3 - MVC");
    resize(400, 300);
}

MVCMainWindow::~MVCMainWindow()
{
}
