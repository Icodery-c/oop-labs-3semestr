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
    QRect getBoundsAfterResize(int dw, int dh) const override;
    QString getName() const override { return "Line"; }

    // Сериализация
    void save(QTextStream& stream) const override;
    void load(QTextStream& stream) override;
    QString getType() const override { return "Line"; }

    void setEndPoint(const QPoint& endPoint, const QRect& bounds);
    QPoint getEndPoint() const { return m_endPoint; }

    void move(int dx, int dy, const QRect& bounds) override;

private:
    bool isPointNearLine(const QPoint& point) const;
    double distanceToLine(const QPoint& point) const;
};
