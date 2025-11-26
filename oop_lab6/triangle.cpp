#include "triangle.h"
#include <QPolygon>
#include <QDebug>

Triangle::Triangle(const QPoint& position, int size, const QColor& color)
    : BaseShape(position, color)
    , m_size(size)
{
}

void Triangle::draw(QPainter& painter) const
{
    painter.save();

    painter.setBrush(QBrush(m_color));
    painter.setPen(QPen(m_borderColor, m_borderWidth));

    QPolygon polygon = getPolygon();
    painter.drawPolygon(polygon);

    if (m_selected) {
        drawSelectionHighlight(painter, getBoundingRect());
    }

    painter.restore();
}

bool Triangle::contains(const QPoint& point) const
{
    return getPolygon().containsPoint(point, Qt::OddEvenFill);
}

QRect Triangle::getBoundingRect() const
{
    QPolygon polygon = getPolygon();
    return polygon.boundingRect();
}

QRect Triangle::getBoundsAfterResize(int dw, int dh) const
{
    int newSize = m_size + dw; // Используем только dw для треугольника
    if (newSize < 10) newSize = 10;

    QPolygon polygon;
    polygon << QPoint(m_position.x(), m_position.y() - newSize/2)
            << QPoint(m_position.x() - newSize/2, m_position.y() + newSize/2)
            << QPoint(m_position.x() + newSize/2, m_position.y() + newSize/2);

    return polygon.boundingRect();
}

void Triangle::setSize(int size, const QRect& bounds)
{
    if (size > 0) {
        int delta = size - m_size;
        if (canResize(delta, delta, bounds)) {
            m_size = size;
            qDebug() << "Triangle size changed to:" << size;
        } else {
            qDebug() << "Triangle cannot resize to" << size << "- out of bounds";
        }
    }
}

QPolygon Triangle::getPolygon() const
{
    QPolygon polygon;
    polygon << QPoint(m_position.x(), m_position.y() - m_size/2)
            << QPoint(m_position.x() - m_size/2, m_position.y() + m_size/2)
            << QPoint(m_position.x() + m_size/2, m_position.y() + m_size/2);
    return polygon;
}
