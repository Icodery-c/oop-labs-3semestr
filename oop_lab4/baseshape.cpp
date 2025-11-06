#include "baseshape.h"
#include <QDebug>


BaseShape::BaseShape(const QPoint& position, const QColor& color)
    : m_position(position)
    , m_color(color)
    , m_borderColor(Qt::black)
    , m_selected(false)
    , m_borderWidth(1)
{
}

void BaseShape::move(int dx, int dy)
{
    m_position += QPoint(dx, dy);
    qDebug() << getName() << "moved to:" << m_position;
}

void BaseShape::setPosition(const QPoint& newPosition)
{
    m_position = newPosition;
}

void BaseShape::setColor(const QColor& color)
{
    m_color = color;
    qDebug() << getName() << "color changed to:" << getColorName();
}

void BaseShape::setBorderColor(const QColor& color)
{
    m_borderColor = color;
}

void BaseShape::setSelected(bool selected)
{
    m_selected = selected;
    qDebug() << getName() << "selection:" << (selected ? "selected" : "deselected");
}

QString BaseShape::getColorName() const
{
    return m_color.name();
}

bool BaseShape::isWithinBounds(const QRect& bounds) const
{
    QRect shapeBounds = getBoundingRect();
    return bounds.contains(shapeBounds);
}

void BaseShape::drawSelectionHighlight(QPainter& painter, const QRect& rect) const
{
    if (m_selected) {
        painter.save();
        QPen selectionPen(Qt::red, 2, Qt::DashLine);
        painter.setPen(selectionPen);
        painter.setBrush(Qt::NoBrush);
        painter.drawRect(rect.adjusted(-2, -2, 2, 2));
        painter.restore();
    }
}
