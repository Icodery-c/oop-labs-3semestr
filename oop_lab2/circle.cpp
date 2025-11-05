#include "circle.h"
#include <cmath>

// Конструктор без параметров
Circle::Circle() : Shape("red", "Circle"), radius(1.0) {
    std::cout << "Circle default constructor" << std::endl;
}

// Конструктор с параметрами
Circle::Circle(const std::string& color, double radius)
    : Shape(color, "Circle"), radius(radius) {
    std::cout << "Circle parameterized constructor, radius: " << radius << std::endl;
}

// Конструктор копирования
Circle::Circle(const Circle& other)
    : Shape(other), radius(other.radius) {
    std::cout << "Circle copy constructor, radius: " << radius << std::endl;
}

// Деструктор
Circle::~Circle() {
    std::cout << "Circle destructor: " << name << " with radius " << radius << std::endl;
}

// Переопределенный метод рисования
void Circle::draw() const {
    std::cout << "Drawing circle: " << color << " circle with radius " << radius;
    std::cout << " (area: " << area() << ")" << std::endl;
}

// Переопределенный метод площади
double Circle::area() const {
    return M_PI * radius * radius;
}

double Circle::getRadius() const {
    return radius;
}

void Circle::setRadius(double radius) {
    this->radius = radius;
}
