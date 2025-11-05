#pragma once
#include <QPainter>

class CCircle
{
private:
    double x, y;
    double radius;
    bool selected;

public:
    CCircle(double x, double y, double r = 50);

    void draw(QPainter &painter) const;
    bool contains(int px, int py) const;
    void setSelected(bool state);
    bool isSelected() const;

    double getRadius() const { return radius; }
    void setRadius(double r) { radius = r; }

};
