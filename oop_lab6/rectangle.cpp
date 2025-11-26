#include "rectangle.h"
#include <QDebug>

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

QRect Rectangle::getBoundsAfterResize(int dw, int dh) const
{
    QSize newSize = m_size + QSize(dw, dh);
    if (newSize.width() < 10) newSize.setWidth(10);
    if (newSize.height() < 10) newSize.setHeight(10);

    return QRect(m_position, newSize);
}

void Rectangle::setSize(const QSize& size, const QRect& bounds)
{
    if (size.width() > 0 && size.height() > 0) {
        int dw = size.width() - m_size.width();
        int dh = size.height() - m_size.height();

        if (canResize(dw, dh, bounds)) {
            m_size = size;
            qDebug() << "Rectangle size changed to:" << size;
        } else {
            qDebug() << "Rectangle cannot resize to" << size << "- out of bounds";
        }
    }
}

QRect Rectangle::getRect() const
{
    return QRect(m_position, m_size);
}

void Rectangle::save(QTextStream& stream) const
{
    stream << getType() << " ";
    saveCommonProperties(stream);
    stream << m_size.width() << " " << m_size.height() << "\n";
}

// Десериализация прямоугольника
void Rectangle::load(QTextStream& stream)
{
    loadCommonProperties(stream);
    int width, height;
    stream >> width >> height;
    m_size = QSize(width, height);
}
