#include "ccircle.h"
#include <cmath>

CCircle::CCircle(double x, double y, double r)
    : x(x), y(y), radius(r), selected(false)
{
}

void CCircle::draw(QPainter &painter) const
{
    painter.setRenderHint(QPainter::Antialiasing, true);
    if (selected) {
        painter.setBrush(QBrush(Qt::yellow)); // выделенные — жёлтые

        painter.setPen(QPen(Qt::red, 2));
    } else {
        painter.setBrush(QBrush(Qt::blue));
        painter.setPen(QPen(Qt::black, 1));
    }
    painter.drawEllipse(QPointF(x, y), radius, radius);
}

bool CCircle::contains(int px, int py) const
{
    double dx = px - x;
    double dy = py - y;
    return std::sqrt(dx * dx + dy * dy) <= radius;
}

void CCircle::setSelected(bool state)
{
    selected = state;
}

bool CCircle::isSelected() const
{
    return selected;
}
