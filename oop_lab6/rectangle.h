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
    QRect getBoundsAfterResize(int dw, int dh) const override;
    QString getName() const override { return "Rectangle"; }

    // Сериализация
    void save(QTextStream& stream) const override;
    void load(QTextStream& stream) override;
    QString getType() const override { return "Rectangle"; }

    void setSize(const QSize& size, const QRect& bounds);
    QSize getSize() const { return m_size; }

private:
    QRect getRect() const;
};
