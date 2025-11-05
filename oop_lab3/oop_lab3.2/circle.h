#pragma once
#include <QPainter>

class CCircle
{
private:
    int m_x, m_y;
    const int m_radius;
    bool m_isSelected;

public:
    CCircle(int x, int y, int radius = 20);
    
    // Методы для проверки и отрисовки
    bool containsPoint(int pointX, int pointY) const;
    void draw(QPainter &painter) const;
    
    // Геттеры и сеттеры
    void setSelected(bool selected);
    bool isSelected() const;
    int getX() const;
    int getY() const;
    int getRadius() const;
};

