#include "shapestorage.h"
#include <algorithm>
#include <QDebug>

#include "circle.h"
#include "rectangle.h"
#include "triangle.h"
#include "line.h"

ShapeStorage::ShapeStorage()
{
}

void ShapeStorage::addShape(std::unique_ptr<BaseShape> shape)
{
    m_shapes.push_back(std::move(shape));
    qDebug() << "Shape added. Total shapes:" << m_shapes.size();
}

void ShapeStorage::removeSelectedShapes()
{
    auto it = std::remove_if(m_shapes.begin(), m_shapes.end(),
        [](const std::unique_ptr<BaseShape>& shape) {
            return shape->isSelected();
        });

    int removedCount = std::distance(it, m_shapes.end());
    m_shapes.erase(it, m_shapes.end());

    if (removedCount > 0) {
        qDebug() << "Removed" << removedCount << "selected shapes";
    }
}

void ShapeStorage::clear()
{
    m_shapes.clear();
    qDebug() << "Storage cleared";
}

int ShapeStorage::getCount() const
{
    return static_cast<int>(m_shapes.size());
}

BaseShape* ShapeStorage::getShape(int index)
{
    if (index >= 0 && index < static_cast<int>(m_shapes.size())) {
        return m_shapes[index].get();
    }
    return nullptr;
}

const BaseShape* ShapeStorage::getShape(int index) const
{
    if (index >= 0 && index < static_cast<int>(m_shapes.size())) {
        return m_shapes[index].get();
    }
    return nullptr;
}

void ShapeStorage::selectShapesAt(const QPoint& point, bool ctrlPressed)
{
    // Находим все фигуры под курсором
    std::vector<int> shapesUnderCursor;
    for (int i = 0; i < static_cast<int>(m_shapes.size()); ++i) {
        if (m_shapes[i]->contains(point)) {
            shapesUnderCursor.push_back(i);
        }
    }

    if (shapesUnderCursor.empty()) {
        // Клик в пустое место - снимаем выделение если не нажат Ctrl
        if (!ctrlPressed) {
            deselectAll();
        }
        return;
    }

    if (!ctrlPressed) {
        // Без Ctrl - выделяем только фигуры под курсором, остальные снимаем
        deselectAll();
        for (int index : shapesUnderCursor) {
            m_shapes[index]->setSelected(true);
        }
    } else {
        // С Ctrl - переключаем выделение фигур под курсором
        for (int index : shapesUnderCursor) {
            m_shapes[index]->setSelected(!m_shapes[index]->isSelected());
        }
    }

    // Логируем результат
    qDebug() << "Selected" << shapesUnderCursor.size() << "shapes under cursor";
    for (int index : shapesUnderCursor) {
        if (m_shapes[index]->isSelected()) {
            qDebug() << " -" << m_shapes[index]->getName() << "at index" << index;
        }
    }
}

void ShapeStorage::deselectAll()
{
    for (auto& shape : m_shapes) {
        shape->setSelected(false);
    }
}

bool ShapeStorage::hasSelectedShapes() const
{
    return std::any_of(m_shapes.begin(), m_shapes.end(),
        [](const std::unique_ptr<BaseShape>& shape) {
            return shape->isSelected();
        });
}

void ShapeStorage::moveSelected(int dx, int dy, const QRect& bounds)
{
    for (auto& shape : m_shapes) {
        if (shape->isSelected()) {
            shape->move(dx, dy, bounds);
        }
    }
}

void ShapeStorage::resizeSelected(int dw, int dh, const QRect& bounds)
{
    for (auto& shape : m_shapes) {
        if (shape->isSelected()) {
            if (auto* circle = dynamic_cast<Circle*>(shape.get())) {
                circle->setRadius(circle->getRadius() + dw, bounds);
            }
            else if (auto* rect = dynamic_cast<Rectangle*>(shape.get())) {
                QSize newSize = rect->getSize() + QSize(dw, dh);
                rect->setSize(newSize, bounds);
            }
            else if (auto* triangle = dynamic_cast<Triangle*>(shape.get())) {
                triangle->setSize(triangle->getSize() + dw, bounds);
            }
            else if (auto* line = dynamic_cast<Line*>(shape.get())) {
                QPoint currentEnd = line->getEndPoint();
                line->setEndPoint(currentEnd + QPoint(dw, dh), bounds);
            }
        }
    }
}

void ShapeStorage::changeSelectedColor(const QColor& color)
{
    for (auto& shape : m_shapes) {
        if (shape->isSelected()) {
            shape->setColor(color);
        }
    }
}

void ShapeStorage::drawAll(QPainter& painter) const
{
    for (const auto& shape : m_shapes) {
        shape->draw(painter);
    }
}

bool ShapeStorage::isShapeAtTop(const BaseShape* shape, const QPoint& point) const
{
    // Проверяем, что нет других фигур поверх этой в данной точке
    for (const auto& other : m_shapes) {
        if (other.get() == shape) {
            break; // Доходим до текущей фигуры - она верхняя
        }
        if (other->contains(point)) {
            return false; // Есть фигура поверх
        }
    }
    return true;
}
