#include "circle.h"
#include <cmath>

Circle::Circle(const QPoint& center, int radius, const QColor& color)
    : BaseShape(center, color)
    , m_radius(radius)
{
}

void Circle::draw(QPainter& painter) const
{
    painter.save();

    // Настройка кисти и пера
    painter.setBrush(QBrush(m_color));
    painter.setPen(QPen(m_borderColor, m_borderWidth));

    // Рисуем круг
    QPoint topLeft = getTopLeft();
    painter.drawEllipse(topLeft.x(), topLeft.y(), m_radius * 2, m_radius * 2);

    // Рисуем выделение если нужно
    if (m_selected) {
        drawSelectionHighlight(painter, getBoundingRect());
    }

    painter.restore();
}

bool Circle::contains(const QPoint& point) const
{
    // Проверяем попадание точки в круг
    int dx = point.x() - m_position.x();
    int dy = point.y() - m_position.y();
    return (dx * dx + dy * dy) <= (m_radius * m_radius);
}

QRect Circle::getBoundingRect() const
{
    QPoint topLeft = getTopLeft();
    return QRect(topLeft, QSize(m_radius * 2, m_radius * 2));
}

void Circle::setRadius(int radius)
{
    if (radius > 0) {
        m_radius = radius;
        qDebug() << "Circle radius changed to:" << radius;
    }
}

QPoint Circle::getTopLeft() const
{
    return QPoint(m_position.x() - m_radius, m_position.y() - m_radius);
}
