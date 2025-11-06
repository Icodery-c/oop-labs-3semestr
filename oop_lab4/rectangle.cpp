#include "rectangle.h"

Rectangle::Rectangle(const QPoint& position, const QSize& size, const QColor& color)
    : BaseShape(position, color)
    , m_size(size)
{
}

void Rectangle::draw(QPainter& painter) const
{
    painter.save();

    painter.setBrush(QBrush(m_color));
    painter.setPen(QPen(m_borderColor, m_borderWidth));

    QRect rect = getRect();
    painter.drawRect(rect);

    if (m_selected) {
        drawSelectionHighlight(painter, rect);
    }

    painter.restore();
}

bool Rectangle::contains(const QPoint& point) const
{
    return getRect().contains(point);
}

QRect Rectangle::getBoundingRect() const
{
    return getRect();
}

void Rectangle::setSize(const QSize& size)
{
    if (size.width() > 0 && size.height() > 0) {
        m_size = size;
        qDebug() << "Rectangle size changed to:" << size;
    }
}

QRect Rectangle::getRect() const
{
    return QRect(m_position, m_size);
}
