#pragma once

#include "shape.h"

class Rectangle : public Shape {
private:
    double width;
    double height;

public:
    // Конструкторы
    Rectangle();
    Rectangle(const std::string& color, double width, double height);
    Rectangle(const Rectangle& other);

    // Деструктор
    ~Rectangle();

    // Переопределенные методы
    void draw() const override;
    double area() const override;

    // Специфичные методы
    double getWidth() const;
    double getHeight() const;
    void setDimensions(double width, double height);
};
