#pragma once

#include <QPainter>

class CCircle {
public:
    void setRadius(int r) { m_radius = r; }
    int radius() const { return m_radius; }
public:
    CCircle(int x, int y, int radius = 50);
    ~CCircle();

    void draw(QPainter &p) const;      // draw itself
    bool isInside(int px, int py) const; // hit-test

    void setSelected(bool s);
    bool isSelected() const;

private:
    int m_x;
    int m_y;
    int m_radius;
    bool m_selected;
};
