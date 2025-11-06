#pragma once

#include <QMainWindow>
#include "shapewidget.h"

class QToolBar;
class QMenu;
class QAction;

class MainWindow : public QMainWindow
{
    Q_OBJECT

private:
    ShapeWidget *m_shapeWidget;
    QToolBar *m_toolBar;

    // Actions для инструментов
    QAction *m_selectAction;
    QAction *m_circleAction;
    QAction *m_rectangleAction;
    QAction *m_triangleAction;
    QAction *m_lineAction;  // ← ДОБАВЛЯЕМ ОБЪЯВЛЕНИЕ
    QAction *m_deleteAction;
    QAction *m_colorAction;
    QAction *m_clearAction;

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void onSelectionChanged();
    void onChangeColor();
    void onClearCanvas();

private:
    void createToolBar();
    void createMenu();
    void updateActions();
};
