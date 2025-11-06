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
    , m_endPoint(startPoint + QPoint(50, 50)) // Линия по умолчанию
{
}

void Line::draw(QPainter& painter) const
{
    painter.save();

    // Для линии используем только перо (без кисти)
    QPen pen(m_color, 3); // Толщина линии 3 пикселя
    if (m_selected) {
        pen.setColor(Qt::red);
        pen.setWidth(4);
    }
    painter.setPen(pen);
    painter.setBrush(Qt::NoBrush);

    // Рисуем линию
    painter.drawLine(m_position, m_endPoint);

    // Если выделена, рисуем маркеры на концах
    if (m_selected) {
        painter.setBrush(QBrush(Qt::red));
        painter.setPen(QPen(Qt::black, 1));

        // Маркеры на концах линии
        painter.drawEllipse(m_position, 4, 4);
        painter.drawEllipse(m_endPoint, 4, 4);

        // Прямоугольник выделения вокруг всей линии
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

void Line::setEndPoint(const QPoint& endPoint)
{
    m_endPoint = endPoint;
}

void Line::move(int dx, int dy)
{
    m_position += QPoint(dx, dy);
    m_endPoint += QPoint(dx, dy);
    qDebug() << "Line moved. Start:" << m_position << "End:" << m_endPoint;
}

bool Line::isPointNearLine(const QPoint& point) const
{
    double distance = distanceToLine(point);
    return distance <= 5.0; // 5 пикселей - область попадания
}

double Line::distanceToLine(const QPoint& point) const
{
    // Вычисляем расстояние от точки до отрезка
    int x1 = m_position.x(), y1 = m_position.y();
    int x2 = m_endPoint.x(), y2 = m_endPoint.y();
    int x0 = point.x(), y0 = point.y();

    // Длина отрезка
    double lineLength = std::sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1));

    if (lineLength == 0) {
        // Если отрезок вырожден в точку
        return std::sqrt((x0 - x1) * (x0 - x1) + (y0 - y1) * (y0 - y1));
    }

    // Проекция точки на прямую
    double t = ((x0 - x1) * (x2 - x1) + (y0 - y1) * (y2 - y1)) / (lineLength * lineLength);
    t = qMax(0.0, qMin(1.0, t)); // Ограничиваем отрезком

    // Ближайшая точка на отрезке
    double closestX = x1 + t * (x2 - x1);
    double closestY = y1 + t * (y2 - y1);

    // Расстояние до ближайшей точки
    return std::sqrt((x0 - closestX) * (x0 - closestX) + (y0 - closestY) * (y0 - closestY));
}
