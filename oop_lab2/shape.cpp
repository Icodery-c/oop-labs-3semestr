#include "shape.h"

// Конструктор без параметров
Shape::Shape() : color("black"), name("Unknown Shape") {
    std::cout << "Shape default constructor: " << name << std::endl;
}

// Конструктор с параметрами
Shape::Shape(const std::string& color, const std::string& name)
    : color(color), name(name) {
    std::cout << "Shape parameterized constructor: " << name << std::endl;
}

// Конструктор копирования
Shape::Shape(const Shape& other)
    : color(other.color), name(other.name + " (copy)") {
    std::cout << "Shape copy constructor: " << name << std::endl;
}

// Деструктор
Shape::~Shape() {
    std::cout << "Shape destructor: " << name << std::endl;
}

// Метод рисования
void Shape::draw() const {
    std::cout << "Drawing " << color << " " << name << std::endl;
}

// Площадь (базовая реализация)
double Shape::area() const {
    std::cout << "Calculating area for " << name << " (base implementation)" << std::endl;
    return 0.0;
}

// Геттеры и сеттеры
std::string Shape::getColor() const {
    return color;
}

std::string Shape::getName() const {
    return name;
}

void Shape::setColor(const std::string& color) {
    this->color = color;
}
