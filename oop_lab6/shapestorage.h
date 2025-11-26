#pragma once


#include "baseshape.h"
#include <vector>
#include <memory>

// Предварительное объявление
class ShapeFactory;

class ShapeStorage
{
private:
    std::vector<std::unique_ptr<BaseShape>> m_shapes;
    ShapeFactory* m_factory;  // ← СЫРОЙ УКАЗАТЕЛЬ вместо unique_ptr

public:
    ShapeStorage();
    ~ShapeStorage();  // ← ДОБАВЛЯЕМ ДЕСТРУКТОР

    void addShape(std::unique_ptr<BaseShape> shape);
    void removeSelectedShapes();
    void clear();

    int getCount() const;
    BaseShape* getShape(int index);
    const BaseShape* getShape(int index) const;

    void selectShapesAt(const QPoint& point, bool ctrlPressed = false);
    void deselectAll();
    bool hasSelectedShapes() const;

    void moveSelected(int dx, int dy, const QRect& bounds);
    void resizeSelected(int dw, int dh, const QRect& bounds);
    void changeSelectedColor(const QColor& color);

    void drawAll(QPainter& painter) const;

    // Группировка
    void groupSelected();
    void ungroupSelected();

    // Сериализация
    bool saveToFile(const QString& filename);
    bool loadFromFile(const QString& filename);

    // Фабрика
    void setFactory(ShapeFactory* factory);  // ← СЫРОЙ УКАЗАТЕЛЬ
};
