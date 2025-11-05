#include "circle.h"
#include <cmath>

CCircle::CCircle(int x, int y, int radius) 
    : m_x(x), m_y(y), m_radius(radius), m_isSelected(false)
{
}

bool CCircle::containsPoint(int pointX, int pointY) const
{
    // Проверяем, находится ли точка внутри круга
    int dx = pointX - m_x;
    int dy = pointY - m_y;
    return (dx * dx + dy * dy) <= (m_radius * m_radius);
}

void CCircle::draw(QPainter &painter) const
{
    if (m_isSelected) {
        painter.setBrush(QBrush(Qt::blue));
        painter.setPen(QPen(Qt::darkBlue, 2));
    } else {
        painter.setBrush(QBrush(Qt::red));
        painter.setPen(QPen(Qt::darkRed, 1));
    }
    
    painter.drawEllipse(m_x - m_radius, m_y - m_radius, 
                       m_radius * 2, m_radius * 2);
}

void CCircle::setSelected(bool selected)
{
    m_isSelected = selected;
}

bool CCircle::isSelected() const
{
    return m_isSelected;
}

int CCircle::getX() const { return m_x; }
int CCircle::getY() const { return m_y; }
int CCircle::getRadius() const { return m_radius; }
