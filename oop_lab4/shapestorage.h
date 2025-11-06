#pragma once

#include "baseshape.h"
#include <vector>
#include <memory>

class ShapeStorage
{
private:
    std::vector<std::unique_ptr<BaseShape>> m_shapes;

public:
    ShapeStorage();

    // Добавление фигур
    void addShape(std::unique_ptr<BaseShape> shape);

    // Удаление
    void removeSelectedShapes();
    void clear();

    // Доступ
    int getCount() const;
    BaseShape* getShape(int index);
    const BaseShape* getShape(int index) const;

    // Работа с выделением
    void selectShapeAt(const QPoint& point, bool ctrlPressed = false);
    void deselectAll();
    bool hasSelectedShapes() const;

    // Манипуляции с выделенными фигурами
    void moveSelected(int dx, int dy);
    void resizeSelected(int dw, int dh);
    void changeSelectedColor(const QColor& color);

    // Отрисовка всех фигур
    void drawAll(QPainter& painter) const;

private:
    bool isShapeAtTop(const BaseShape* shape, const QPoint& point) const;
};
