#pragma once

#include "baseshape.h"

class Triangle : public BaseShape
{
private:
    int m_size;

public:
    Triangle(const QPoint& position, int size = 80, const QColor& color = Qt::red);

    void draw(QPainter& painter) const override;
    bool contains(const QPoint& point) const override;
    QRect getBoundingRect() const override;
    QRect getBoundsAfterResize(int dw, int dh) const override;
    QString getName() const override { return "Triangle"; }

    void setSize(int size, const QRect& bounds);
    int getSize() const { return m_size; }

private:
    QPolygon getPolygon() const;
};
