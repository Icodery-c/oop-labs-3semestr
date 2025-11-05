#pragma once
#include <QMainWindow>
#include <QPushButton>

class CircleWidget;

class MainWindow : public QMainWindow
{
    Q_OBJECT

private:
    CircleWidget *m_circleWidget;
    QPushButton *m_deleteButton;

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void onDeleteClicked();
    void onCirclesChanged();
};


