#include "triangle.h"
#include <QPolygon>

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

void Triangle::setSize(int size)
{
    if (size > 0) {
        m_size = size;
        qDebug() << "Triangle size changed to:" << size;
    }
}

QPolygon Triangle::getPolygon() const
{
    QPolygon polygon;
    polygon << QPoint(m_position.x(), m_position.y() - m_size/2)      // Верхняя точка
            << QPoint(m_position.x() - m_size/2, m_position.y() + m_size/2)  // Левая нижняя
            << QPoint(m_position.x() + m_size/2, m_position.y() + m_size/2); // Правая нижняя
    return polygon;
}
