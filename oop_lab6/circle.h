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
    QRect getBoundsAfterResize(int dw, int dh) const override;
    QString getName() const override { return "Circle"; }

    // Сериализация
    void save(QTextStream& stream) const override;
    void load(QTextStream& stream) override;
    QString getType() const override { return "Circle"; }

    // Специфичные методы для круга
    void setRadius(int radius, const QRect& bounds);
    int getRadius() const { return m_radius; }

private:
    QPoint getTopLeft() const;
};
