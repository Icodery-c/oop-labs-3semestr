#pragma once

#include "shape.h"

class Circle : public Shape {
private:
    double radius;
    Point center;

public:
    // Конструкторы
    Circle();
    Circle(const std::string& color, double radius);
    Circle(const Circle& other);

    // Деструктор
    ~Circle();

    // Переопределенные методы
    void draw() const override;
    double area() const override;

    // Специфичные методы
    double getRadius() const;
    void setRadius(double radius);
};
