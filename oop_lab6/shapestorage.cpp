#include "shapestorage.h"
#include "shapefactory.h"
#include "circle.h"
#include "rectangle.h"
#include "triangle.h"
#include "line.h"
#include "group.h"
#include <algorithm>
#include <QDebug>
#include <QFile>
#include <QTextStream>
#include <QFileInfo>

ShapeStorage::ShapeStorage()
    : m_factory(nullptr)  // инициализируем nullptr
{
}

ShapeStorage::~ShapeStorage()
{
    // Не удаляем фабрику, так как она управляется извне
}

void ShapeStorage::setFactory(ShapeFactory* factory)
{
    m_factory = factory;
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
    if (!ctrlPressed) {
        deselectAll();
    }

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

// void ShapeStorage::setFactory(std::unique_ptr<ShapeFactory> factory)
// {
//     m_factory = std::move(factory);
// }

bool ShapeStorage::saveToFile(const QString& filename)
{
    QFile file(filename);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        qDebug() << "Cannot open file for writing:" << filename;
        qDebug() << "Error:" << file.errorString();
        return false;
    }

    QTextStream stream(&file);

    // Сохраняем количество объектов
    stream << m_shapes.size() << "\n";

    // Сохраняем каждый объект
    for (const auto& shape : m_shapes) {
        shape->save(stream);
    }

    file.close();
    qDebug() << "Saved" << m_shapes.size() << "shapes to" << filename;

    // Проверим, что файл действительно создался
    QFileInfo fileInfo(filename);
    qDebug() << "File exists:" << fileInfo.exists();
    qDebug() << "File size:" << fileInfo.size() << "bytes";

    return true;
}

bool ShapeStorage::loadFromFile(const QString& filename)
{
    if (!m_factory) {
        qDebug() << "Factory not set!";
        return false;
    }

    QFile file(filename);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "Cannot open file for reading:" << filename;
        qDebug() << "Error:" << file.errorString();
        return false;
    }

    // Проверим размер файла
    QFileInfo fileInfo(filename);
    qDebug() << "Loading file:" << filename;
    qDebug() << "File size:" << fileInfo.size() << "bytes";

    QTextStream stream(&file);

    // Читаем количество объектов
    int count;
    stream >> count;
    qDebug() << "Objects count in file:" << count;

    // Очищаем текущие фигуры
    m_shapes.clear();

    // Загружаем каждый объект
    int loadedCount = 0;
    for (int i = 0; i < count; ++i) {
        auto shape = m_factory->loadShape(stream);
        if (shape) {
            m_shapes.push_back(std::move(shape));
            loadedCount++;
            qDebug() << "Loaded shape" << i << "type:" << m_shapes.back()->getType();
        } else {
            qDebug() << "Failed to load shape" << i;
        }
    }

    file.close();
    qDebug() << "Successfully loaded" << loadedCount << "shapes from" << filename;
    return loadedCount > 0;
}

void ShapeStorage::groupSelected()
{
    // Находим все выделенные фигуры
    std::vector<std::unique_ptr<BaseShape>> selectedShapes;

    auto it = std::remove_if(m_shapes.begin(), m_shapes.end(),
        [&selectedShapes](std::unique_ptr<BaseShape>& shape) {
            if (shape->isSelected()) {
                selectedShapes.push_back(std::move(shape));
                return true;
            }
            return false;
        });

    m_shapes.erase(it, m_shapes.end());

    if (selectedShapes.size() > 1) {
        // Создаем группу и добавляем в нее выделенные фигуры
        auto group = std::make_unique<Group>();
        for (auto& shape : selectedShapes) {
            group->addShape(std::move(shape));
        }

        // Добавляем группу обратно в хранилище
        m_shapes.push_back(std::move(group));
        qDebug() << "Created group with" << selectedShapes.size() << "shapes";
    } else if (selectedShapes.size() == 1) {
        // Если выделена только одна фигура - возвращаем ее обратно
        m_shapes.push_back(std::move(selectedShapes[0]));
        qDebug() << "Need at least 2 shapes to create a group";
    }
}

void ShapeStorage::ungroupSelected()
{
    std::vector<std::unique_ptr<BaseShape>> shapesToAdd;

    auto it = std::remove_if(m_shapes.begin(), m_shapes.end(),
        [&shapesToAdd](std::unique_ptr<BaseShape>& shape) {
            if (shape->isSelected()) {
                if (auto* group = dynamic_cast<Group*>(shape.get())) {
                    // Извлекаем все фигуры из группы
                    for (int i = 0; i < group->getChildCount(); ++i) {
                        //auto child = group->getChild(i);
                        // Создаем копию фигуры (в реальной реализации нужен метод clone())
                        // shapesToAdd.push_back(child->clone());
                    }
                    qDebug() << "Ungrouped group with" << group->getChildCount() << "children";
                    return true;
                }
            }
            return false;
        });

    m_shapes.erase(it, m_shapes.end());

    // Добавляем извлеченные фигуры обратно в хранилище
    for (auto& shape : shapesToAdd) {
        m_shapes.push_back(std::move(shape));
    }
}
