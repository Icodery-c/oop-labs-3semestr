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
#include <QFileDialog>
#include "group.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{

  qDebug() << "Current directory:" << QDir::currentPath();
  qDebug() << "Home directory:" << QDir::homePath();
  
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
    setWindowTitle("Визуальный редактор - Лабораторная работа 6");
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
    QActionGroup *toolGroup = new QActionGroup(this);
    toolGroup->addAction(m_selectAction);
    toolGroup->addAction(m_circleAction);
    toolGroup->addAction(m_rectangleAction);
    toolGroup->addAction(m_triangleAction);
    toolGroup->addAction(m_lineAction);
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

    // Действия группировки
    m_groupAction = new QAction("Группировать", this);
    m_groupAction->setShortcut(QKeySequence("Ctrl+G"));
    connect(m_groupAction, &QAction::triggered, this, [this]() {
        m_shapeWidget->getStorage().groupSelected();
        m_shapeWidget->update();
        onSelectionChanged();
    });

    m_ungroupAction = new QAction("Разгруппировать", this);
    m_ungroupAction->setShortcut(QKeySequence("Ctrl+U"));
    connect(m_ungroupAction, &QAction::triggered, this, [this]() {
        m_shapeWidget->getStorage().ungroupSelected();
        m_shapeWidget->update();
        onSelectionChanged();
    });

    // Добавляем действия на панель инструментов
    m_toolBar->addAction(m_selectAction);
    m_toolBar->addAction(m_circleAction);
    m_toolBar->addAction(m_rectangleAction);
    m_toolBar->addAction(m_triangleAction);
    m_toolBar->addAction(m_lineAction);
    m_toolBar->addSeparator();
    m_toolBar->addAction(m_deleteAction);
    m_toolBar->addAction(m_colorAction);
    m_toolBar->addSeparator();
    m_toolBar->addAction(m_groupAction);
    m_toolBar->addAction(m_ungroupAction);
    m_toolBar->addSeparator();
    m_toolBar->addAction(m_clearAction);
}

void MainWindow::createMenu()
{
    // Меню Файл
    QMenu *fileMenu = menuBar()->addMenu("Файл");

    QAction *newAction = new QAction("Новый", this);
    newAction->setShortcut(QKeySequence::New);
    connect(newAction, &QAction::triggered, this, &MainWindow::onClearCanvas);

    QAction *saveAction = new QAction("Сохранить", this);
saveAction->setShortcut(QKeySequence::Save);
connect(saveAction, &QAction::triggered, this, [this]() {
    QString filename = QFileDialog::getSaveFileName(this,
        "Сохранить проект",
        "my_project.shp",
        "Shape Files (*.shp);;All Files (*)");

    if (!filename.isEmpty()) {
        // Автоматически добавляем расширение .shp если его нет
        if (!filename.endsWith(".shp", Qt::CaseInsensitive)) {
            filename += ".shp";
        }

        if (m_shapeWidget->getStorage().saveToFile(filename)) {
            statusBar()->showMessage("Проект сохранен: " + filename);
        } else {
            QMessageBox::warning(this, "Ошибка", "Не удалось сохранить проект");
        }
    }
});

    QAction *loadAction = new QAction("Загрузить", this);
    loadAction->setShortcut(QKeySequence::Open);
    connect(loadAction, &QAction::triggered, this, [this]() {
      QString filename = QFileDialog::getOpenFileName(this,
          "Загрузить проект",
          "",
          "Shape Files (*.shp);;All Files (*)");
                  if (!filename.isEmpty()) {
            if (m_shapeWidget->getStorage().loadFromFile(filename)) {
                m_shapeWidget->update();
                statusBar()->showMessage("Проект загружен: " + filename);
                emit m_shapeWidget->shapesCountChanged(m_shapeWidget->getStorage().getCount());
                onSelectionChanged();
            } else {
                QMessageBox::warning(this, "Ошибка", "Не удалось загрузить проект");
            }
        }
    });

    QAction *exitAction = new QAction("Выход", this);
    exitAction->setShortcut(QKeySequence::Quit);
    connect(exitAction, &QAction::triggered, this, &QMainWindow::close);

    fileMenu->addAction(newAction);
    fileMenu->addAction(saveAction);
    fileMenu->addAction(loadAction);
    fileMenu->addSeparator();
    fileMenu->addAction(exitAction);

    // Меню Правка
    QMenu *editMenu = menuBar()->addMenu("Правка");
    editMenu->addAction(m_deleteAction);
    editMenu->addAction(m_colorAction);
    editMenu->addAction(m_groupAction);
    editMenu->addAction(m_ungroupAction);
    editMenu->addSeparator();

    QAction *selectAllAction = new QAction("Выделить все", this);
    selectAllAction->setShortcut(QKeySequence::SelectAll);
    connect(selectAllAction, &QAction::triggered, this, [this]() {
        // Временная реализация - выделяем все фигуры
        for (int i = 0; i < m_shapeWidget->getStorage().getCount(); ++i) {
            m_shapeWidget->getStorage().getShape(i)->setSelected(true);
        }
        m_shapeWidget->update();
        onSelectionChanged();
        statusBar()->showMessage("Все фигуры выделены");
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

    QAction *aboutAction = new QAction("О программе", this);
    connect(aboutAction, &QAction::triggered, this, []() {
        QMessageBox::about(nullptr, "О программе",
            "Визуальный редактор\n"
            "Лабораторная работа 6\n\n"
            "Управление:\n"
            "• ЛКМ - создать/выделить фигуру\n"
            "• Ctrl+ЛКМ - множественное выделение\n"
            "• Стрелки - перемещение\n"
            "• Ctrl+± - изменение размера\n"
            "• Delete - удаление выделенных\n"
            "• S,C,R,T,L - выбор инструментов\n"
            "• Ctrl+G - группировка\n"
            "• Ctrl+U - разгруппировка");
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

    // Подсчет выделенных фигур для группировки
    int selectedCount = 0;
    bool canUngroup = false;

    for (int i = 0; i < m_shapeWidget->getStorage().getCount(); ++i) {
        if (m_shapeWidget->getStorage().getShape(i)->isSelected()) {
            selectedCount++;

            // Проверяем, является ли выделенная фигура группой
            if (m_shapeWidget->getStorage().getShape(i)->getType() == "Group") {
                canUngroup = true;
            }
        }
    }

    bool canGroup = selectedCount >= 2;

    m_deleteAction->setEnabled(hasSelection);
    m_colorAction->setEnabled(hasSelection);
    m_groupAction->setEnabled(canGroup);
    m_ungroupAction->setEnabled(canUngroup);
}
