#pragma once

#include "baseshape.h"

class Line : public BaseShape
{
private:
    QPoint m_endPoint;

public:
    Line(const QPoint& startPoint, const QPoint& endPoint, const QColor& color = Qt::black);
    Line(const QPoint& startPoint, const QColor& color = Qt::black);

    void draw(QPainter& painter) const override;
    bool contains(const QPoint& point) const override;
    QRect getBoundingRect() const override;
    QString getName() const override { return "Line"; }

    void setEndPoint(const QPoint& endPoint);
    QPoint getEndPoint() const { return m_endPoint; }

    // Переопределяем move для перемещения всей линии
    void move(int dx, int dy) override;  // ← ОСТАВЛЯЕМ override (если move виртуальный в BaseShape)

private:
    bool isPointNearLine(const QPoint& point) const;
    double distanceToLine(const QPoint& point) const;
};
