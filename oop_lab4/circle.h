#pragma once

#include "baseshape.h"

class Circle : public BaseShape
{
private:
    int m_radius;

public:
    Circle(const QPoint& center, int radius = 50, const QColor& color = Qt::blue);

    // Реализация виртуальных методов
    void draw(QPainter& painter) const override;
    bool contains(const QPoint& point) const override;
    QRect getBoundingRect() const override;
    QString getName() const override { return "Circle"; }

    // Специфичные методы для круга
    void setRadius(int radius);
    int getRadius() const { return m_radius; }

private:
    QPoint getTopLeft() const;
};
