#include "line.h"
#include <cmath>
#include <QDebug>

Line::Line(const QPoint& startPoint, const QPoint& endPoint, const QColor& color)
    : BaseShape(startPoint, color)
    , m_endPoint(endPoint)
{
}

Line::Line(const QPoint& startPoint, const QColor& color)
    : BaseShape(startPoint, color)
    , m_endPoint(startPoint + QPoint(50, 50))
{
}

void Line::draw(QPainter& painter) const
{
    painter.save();

    QPen pen(m_color, 3);
    if (m_selected) {
        pen.setColor(Qt::red);
        pen.setWidth(4);
    }
    painter.setPen(pen);
    painter.setBrush(Qt::NoBrush);

    painter.drawLine(m_position, m_endPoint);

    if (m_selected) {
        painter.setBrush(QBrush(Qt::red));
        painter.setPen(QPen(Qt::black, 1));

        painter.drawEllipse(m_position, 4, 4);
        painter.drawEllipse(m_endPoint, 4, 4);

        drawSelectionHighlight(painter, getBoundingRect());
    }

    painter.restore();
}

bool Line::contains(const QPoint& point) const
{
    return isPointNearLine(point);
}

QRect Line::getBoundingRect() const
{
    int minX = qMin(m_position.x(), m_endPoint.x());
    int minY = qMin(m_position.y(), m_endPoint.y());
    int maxX = qMax(m_position.x(), m_endPoint.x());
    int maxY = qMax(m_position.y(), m_endPoint.y());

    return QRect(minX - 5, minY - 5, maxX - minX + 10, maxY - minY + 10);
}

QRect Line::getBoundsAfterResize(int dw, int dh) const
{
    QPoint newEndPoint = m_endPoint + QPoint(dw, dh);

    int minX = qMin(m_position.x(), newEndPoint.x());
    int minY = qMin(m_position.y(), newEndPoint.y());
    int maxX = qMax(m_position.x(), newEndPoint.x());
    int maxY = qMax(m_position.y(), newEndPoint.y());

    return QRect(minX - 5, minY - 5, maxX - minX + 10, maxY - minY + 10);
}

void Line::setEndPoint(const QPoint& endPoint, const QRect& bounds)
{
    int dw = endPoint.x() - m_endPoint.x();
    int dh = endPoint.y() - m_endPoint.y();

    if (canResize(dw, dh, bounds)) {
        m_endPoint = endPoint;
        qDebug() << "Line end point changed to:" << endPoint;
    } else {
        qDebug() << "Line cannot resize to" << endPoint << "- out of bounds";
    }
}

void Line::move(int dx, int dy, const QRect& bounds)
{
    if (canMove(dx, dy, bounds)) {
        m_position += QPoint(dx, dy);
        m_endPoint += QPoint(dx, dy);
        qDebug() << "Line moved. Start:" << m_position << "End:" << m_endPoint;
    } else {
        qDebug() << "Line cannot move - out of bounds";
    }
}

bool Line::isPointNearLine(const QPoint& point) const
{
    double distance = distanceToLine(point);
    return distance <= 5.0;
}

double Line::distanceToLine(const QPoint& point) const
{
    int x1 = m_position.x(), y1 = m_position.y();
    int x2 = m_endPoint.x(), y2 = m_endPoint.y();
    int x0 = point.x(), y0 = point.y();

    double lineLength = std::sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1));

    if (lineLength == 0) {
        return std::sqrt((x0 - x1) * (x0 - x1) + (y0 - y1) * (y0 - y1));
    }

    double t = ((x0 - x1) * (x2 - x1) + (y0 - y1) * (y2 - y1)) / (lineLength * lineLength);
    t = qMax(0.0, qMin(1.0, t));

    double closestX = x1 + t * (x2 - x1);
    double closestY = y1 + t * (y2 - y1);

    return std::sqrt((x0 - closestX) * (x0 - closestX) + (y0 - closestY) * (y0 - closestY));
}

// Сериализация линии
void Line::save(QTextStream& stream) const
{
    stream << getType() << " ";
    saveCommonProperties(stream);
    stream << m_endPoint.x() << " " << m_endPoint.y() << "\n";
}

// Десериализация линии
void Line::load(QTextStream& stream)
{
    loadCommonProperties(stream);
    int endX, endY;
    stream >> endX >> endY;
    m_endPoint = QPoint(endX, endY);
}
