#include "ccircle.h"
#include <cmath>

CCircle::CCircle(int x, int y, int radius)
    : m_x(x), m_y(y), m_radius(radius), m_selected(false)
{
}

CCircle::~CCircle() {}

void CCircle::draw(QPainter &p) const
{
    QRect rect(m_x - m_radius, m_y - m_radius, m_radius * 2, m_radius * 2);

    // fill
    p.setBrush(m_selected ? Qt::yellow : Qt::lightGray);
    p.setPen(Qt::black);
    p.drawEllipse(rect);

    // if selected, draw an outline
    if (m_selected) {
        QPen pen(Qt::red);
        pen.setWidth(2);
        p.setPen(pen);
        p.setBrush(Qt::NoBrush);
        p.drawEllipse(rect);
    }
}

bool CCircle::isInside(int px, int py) const
{
    // distance from center
    int dx = px - m_x;
    int dy = py - m_y;
    long long dist2 = 1LL * dx * dx + 1LL * dy * dy;
    return dist2 <= 1LL * m_radius * m_radius;
}

void CCircle::setSelected(bool s) { m_selected = s; }
bool CCircle::isSelected() const { return m_selected; }
