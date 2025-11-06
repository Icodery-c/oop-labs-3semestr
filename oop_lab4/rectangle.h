#pragma once

#include "baseshape.h"

class Rectangle : public BaseShape
{
private:
    QSize m_size;

public:
    Rectangle(const QPoint& position, const QSize& size = QSize(100, 80),
              const QColor& color = Qt::green);

    void draw(QPainter& painter) const override;
    bool contains(const QPoint& point) const override;
    QRect getBoundingRect() const override;
    QString getName() const override { return "Rectangle"; }

    void setSize(const QSize& size);
    QSize getSize() const { return m_size; }

private:
    QRect getRect() const;
};
