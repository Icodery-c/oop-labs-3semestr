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

void BaseShape::move(int dx, int dy, const QRect& bounds)
{
    if (canMove(dx, dy, bounds)) {
        m_position += QPoint(dx, dy);
        qDebug() << getName() << "moved to:" << m_position;
    } else {
        qDebug() << getName() << "cannot move - out of bounds";
    }
}

bool BaseShape::canMove(int dx, int dy, const QRect& bounds) const
{
    QRect newBounds = getBoundsAfterMove(dx, dy);
    return bounds.contains(newBounds);
}

bool BaseShape::canResize(int dw, int dh, const QRect& bounds) const
{
    QRect newBounds = getBoundsAfterResize(dw, dh);
    return bounds.contains(newBounds);
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

QRect BaseShape::getBoundsAfterMove(int dx, int dy) const
{
    QRect currentBounds = getBoundingRect();
    return currentBounds.translated(dx, dy);
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
