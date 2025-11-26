#include "mainwindow.h"
#include <QToolBar>
#include <QMenu>
#include <QAction>
#include <QMenuBar>
#include <QStatusBar>
#include <QColorDialog>
#include <QMessageBox>
#include <QIcon>
#include <QKeySequence>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    // Создаем центральный виджет
    m_shapeWidget = new ShapeWidget(this);
    setCentralWidget(m_shapeWidget);

    // Создаем интерфейс
    createToolBar();
    createMenu();

    // Подключаем сигналы
    connect(m_shapeWidget, &ShapeWidget::selectionChanged,
            this, &MainWindow::onSelectionChanged);
    connect(m_shapeWidget, &ShapeWidget::shapesCountChanged,
            this, [this](int count) {
                statusBar()->showMessage(QString("Фигур на холсте: %1").arg(count));
            });

    // Настраиваем окно
    setWindowTitle("Визуальный редактор - Лабораторная работа 4");
    resize(800, 600);

    // Статус бар
    statusBar()->showMessage("Готов к работе");

    // Обновляем состояние действий
    updateActions();
}

MainWindow::~MainWindow()
{
}

void MainWindow::createToolBar()
{
    m_toolBar = addToolBar("Инструменты");

    // Действие выбора
    m_selectAction = new QAction("Выделение", this);
    m_selectAction->setCheckable(true);
    m_selectAction->setChecked(true);
    m_selectAction->setShortcut(QKeySequence("S"));
    connect(m_selectAction, &QAction::triggered, this, [this]() {
        m_shapeWidget->setCurrentTool(ShapeWidget::Tool::Select);
    });

    // Действие круга
    m_circleAction = new QAction("Круг", this);
    m_circleAction->setCheckable(true);
    m_circleAction->setShortcut(QKeySequence("C"));
    connect(m_circleAction, &QAction::triggered, this, [this]() {
        m_shapeWidget->setCurrentTool(ShapeWidget::Tool::Circle);
    });

    // Действие прямоугольника
    m_rectangleAction = new QAction("Прямоугольник", this);
    m_rectangleAction->setCheckable(true);
    m_rectangleAction->setShortcut(QKeySequence("R"));
    connect(m_rectangleAction, &QAction::triggered, this, [this]() {
        m_shapeWidget->setCurrentTool(ShapeWidget::Tool::Rectangle);
    });

    // Действие треугольника
    m_triangleAction = new QAction("Треугольник", this);
    m_triangleAction->setCheckable(true);
    m_triangleAction->setShortcut(QKeySequence("T"));
    connect(m_triangleAction, &QAction::triggered, this, [this]() {
        m_shapeWidget->setCurrentTool(ShapeWidget::Tool::Triangle);
    });

    // Действие линии
    m_lineAction = new QAction("Линия", this);
    m_lineAction->setCheckable(true);
    m_lineAction->setShortcut(QKeySequence("L"));
    connect(m_lineAction, &QAction::triggered, this, [this]() {
        m_shapeWidget->setCurrentTool(ShapeWidget::Tool::Line);
    });

    // Группа для эксклюзивного выбора инструментов
    QActionGroup *toolGroup = new QActionGroup(this);  // ← ОБЪЯВЛЯЕМ ПЕРЕМЕННУЮ
    toolGroup->addAction(m_selectAction);
    toolGroup->addAction(m_circleAction);
    toolGroup->addAction(m_rectangleAction);
    toolGroup->addAction(m_triangleAction);
    toolGroup->addAction(m_lineAction);  // ← ДОБАВЛЯЕМ ЛИНИЮ В ГРУППУ
    toolGroup->setExclusive(true);

    // Действия управления
    m_deleteAction = new QAction("Удалить", this);
    m_deleteAction->setShortcut(QKeySequence::Delete);
    connect(m_deleteAction, &QAction::triggered, this, [this]() {
        m_shapeWidget->deleteSelectedShapes();
    });

    m_colorAction = new QAction("Изменить цвет", this);
    m_colorAction->setShortcut(QKeySequence("Ctrl+L"));
    connect(m_colorAction, &QAction::triggered, this, &MainWindow::onChangeColor);

    m_clearAction = new QAction("Очистить", this);
    connect(m_clearAction, &QAction::triggered, this, &MainWindow::onClearCanvas);

    // Добавляем действия на панель инструментов
    m_toolBar->addAction(m_selectAction);
    m_toolBar->addAction(m_circleAction);
    m_toolBar->addAction(m_rectangleAction);
    m_toolBar->addAction(m_triangleAction);
    m_toolBar->addAction(m_lineAction);  // ← ДОБАВЛЯЕМ КНОПКУ ЛИНИИ
    m_toolBar->addSeparator();
    m_toolBar->addAction(m_deleteAction);
    m_toolBar->addAction(m_colorAction);
    m_toolBar->addSeparator();
    m_toolBar->addAction(m_clearAction);
}


//создание меню
void MainWindow::createMenu()
{
    // Меню Файл
    QMenu *fileMenu = menuBar()->addMenu("Файл");

    QAction *newAction = new QAction("Новый", this);
    newAction->setShortcut(QKeySequence::New);
    connect(newAction, &QAction::triggered, this, &MainWindow::onClearCanvas);

    QAction *exitAction = new QAction("Выход", this);
    exitAction->setShortcut(QKeySequence::Quit);
    connect(exitAction, &QAction::triggered, this, &QMainWindow::close);

    fileMenu->addAction(newAction);
    fileMenu->addSeparator();
    fileMenu->addAction(exitAction);

    // Меню Правка
    QMenu *editMenu = menuBar()->addMenu("Правка");
    editMenu->addAction(m_deleteAction);
    editMenu->addAction(m_colorAction);
    editMenu->addSeparator();

    QAction *selectAllAction = new QAction("Выделить все", this);
    selectAllAction->setShortcut(QKeySequence::SelectAll);
    connect(selectAllAction, &QAction::triggered, this, [this]() {
        statusBar()->showMessage("Выделение всех фигур - в разработке");
    });
    editMenu->addAction(selectAllAction);

    QAction *deselectAllAction = new QAction("Снять выделение", this);
    deselectAllAction->setShortcut(QKeySequence("Ctrl+D"));
    connect(deselectAllAction, &QAction::triggered, this, [this]() {
        m_shapeWidget->getStorage().deselectAll();
        m_shapeWidget->update();
        onSelectionChanged();
    });
    editMenu->addAction(deselectAllAction);

    // Меню Вид
    QMenu *viewMenu = menuBar()->addMenu("Вид");
    viewMenu->addAction(m_toolBar->toggleViewAction());

    // Меню Справка
    QMenu *helpMenu = menuBar()->addMenu("Справка");

    // УДАЛЯЕМ ДУБЛИРОВАНИЕ - оставляем только один aboutAction
    QAction *aboutAction = new QAction("О программе", this);
    connect(aboutAction, &QAction::triggered, this, []() {
        QMessageBox::about(nullptr, "О программе",
            "Визуальный редактор\n"
            "Лабораторная работа 4\n\n"
            "Управление:\n"
            "• ЛКМ - создать/выделить фигуру\n"
            "• Ctrl+ЛКМ - множественное выделение\n"
            "• Стрелки - перемещение\n"
            "• Ctrl+± - изменение размера\n"
            "• Delete - удаление выделенных\n"
            "• S,C,R,T,L - выбор инструментов");
    });
    helpMenu->addAction(aboutAction);
}

void MainWindow::onSelectionChanged()
{
    updateActions();

    // Обновляем статус бар
    if (m_shapeWidget->getStorage().hasSelectedShapes()) {
        statusBar()->showMessage("Есть выделенные фигуры");
    } else {
        statusBar()->showMessage("Нет выделенных фигур");
    }
}

void MainWindow::onChangeColor()
{
    if (!m_shapeWidget->getStorage().hasSelectedShapes()) {
        QMessageBox::information(this, "Информация", "Сначала выделите фигуры");
        return;
    }

    QColor color = QColorDialog::getColor(Qt::blue, this, "Выберите цвет");
    if (color.isValid()) {
        m_shapeWidget->changeSelectedColor(color);
        statusBar()->showMessage("Цвет изменен");
    }
}

void MainWindow::onClearCanvas()
{
    int result = QMessageBox::question(this, "Очистка холста",
        "Вы уверены, что хотите очистить весь холст?",
        QMessageBox::Yes | QMessageBox::No);

    if (result == QMessageBox::Yes) {
        m_shapeWidget->getStorage().clear();
        m_shapeWidget->update();
        statusBar()->showMessage("Холст очищен");
        emit m_shapeWidget->shapesCountChanged(0);
    }
}

void MainWindow::updateActions()
{
    bool hasSelection = m_shapeWidget->getStorage().hasSelectedShapes();

    m_deleteAction->setEnabled(hasSelection);
    m_colorAction->setEnabled(hasSelection);
}
