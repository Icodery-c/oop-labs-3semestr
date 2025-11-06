#include "shapewidget.h"
#include <QPainter>
#include <QMouseEvent>
#include <QKeyEvent>
#include "circle.h"
#include "rectangle.h"
#include "triangle.h"
#include "line.h"
#include <QDebug>

ShapeWidget::ShapeWidget(QWidget *parent)
    : QWidget(parent)
    , m_currentTool(Tool::Select)
{
    setFocusPolicy(Qt::StrongFocus);
    setMinimumSize(600, 500);
    setMouseTracking(true);
}

void ShapeWidget::setCurrentTool(Tool tool)
{
    m_currentTool = tool;

    // При смене инструмента снимаем выделение
    if (tool != Tool::Select) {
        m_storage.deselectAll();
        update();
        emit selectionChanged();
    }
}

void ShapeWidget::deleteSelectedShapes()
{
    m_storage.removeSelectedShapes();
    update();
    emit shapesCountChanged(m_storage.getCount());
    emit selectionChanged();
}

void ShapeWidget::changeSelectedColor(const QColor& color)
{
    m_storage.changeSelectedColor(color);
    update();
}

void ShapeWidget::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    // Фон
    painter.fillRect(rect(), QColor(240, 240, 240));

    // Сетка для удобства
    painter.setPen(QPen(QColor(220, 220, 220), 1));
    for (int x = 0; x < width(); x += 20) {
        painter.drawLine(x, 0, x, height());
    }
    for (int y = 0; y < height(); y += 20) {
        painter.drawLine(0, y, width(), y);
    }

    // Все фигуры
    m_storage.drawAll(painter);

    // Информация о состоянии
    QString toolName;
    switch (m_currentTool) {
    case Tool::Select: toolName = "Select"; break;
    case Tool::Circle: toolName = "Circle"; break;
    case Tool::Rectangle: toolName = "Rectangle"; break;
    case Tool::Triangle: toolName = "Triangle"; break;
    case Tool::Line: toolName = "Line"; break;
    }


    painter.drawText(10, 20,
        QString("Фигур: %1 | Инструмент: %2 | Выделено: %3")
            .arg(m_storage.getCount())
            .arg(toolName)
            .arg(m_storage.hasSelectedShapes() ? "Да" : "Нет"));
}

void ShapeWidget::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        if (m_currentTool == Tool::Select) {
            // Режим выделения
            bool ctrlPressed = event->modifiers() & Qt::ControlModifier;
            m_storage.selectShapeAt(event->pos(), ctrlPressed);
            emit selectionChanged();
        } else {
            // Режим создания фигур
            createShapeAt(event->pos());
            emit shapesCountChanged(m_storage.getCount());
        }
        update();
    }
}

void ShapeWidget::keyPressEvent(QKeyEvent *event)
{
    bool handled = true;
    int step = 5;

    switch (event->key()) {
    case Qt::Key_Delete:
        deleteSelectedShapes();
        break;

    case Qt::Key_Left:
        m_storage.moveSelected(-step, 0);
        update();
        break;
    case Qt::Key_Right:
        m_storage.moveSelected(step, 0);
        update();
        break;
    case Qt::Key_Up:
        m_storage.moveSelected(0, -step);
        update();
        break;
    case Qt::Key_Down:
        m_storage.moveSelected(0, step);
        update();
        break;

    case Qt::Key_Plus:
    case Qt::Key_Equal:
        if (event->modifiers() & Qt::ControlModifier) {
            m_storage.resizeSelected(5, 5);
            update();
        }
        break;
    case Qt::Key_Minus:
        if (event->modifiers() & Qt::ControlModifier) {
            m_storage.resizeSelected(-5, -5);
            update();
        }
        break;

    default:
        handled = false;
        break;
    }

    if (handled) {
        event->accept();
    } else {
        QWidget::keyPressEvent(event);
    }
}

void ShapeWidget::createShapeAt(const QPoint& position)
{
    std::unique_ptr<BaseShape> shape;

    switch (m_currentTool) {
    case Tool::Circle:
        shape = std::make_unique<Circle>(position, 30, QColor(0, 100, 255));
        break;
    case Tool::Rectangle:
        shape = std::make_unique<Rectangle>(position, QSize(80, 60), QColor(0, 200, 100));
        break;
    case Tool::Triangle:
        shape = std::make_unique<Triangle>(position, 70, QColor(255, 100, 0));
        break;
    case Tool::Line:
        shape = std::make_unique<Line>(position, QColor(0, 0, 0)); // Черная линия
        break;
    default:
        return;
    }

    m_storage.addShape(std::move(shape));
}
