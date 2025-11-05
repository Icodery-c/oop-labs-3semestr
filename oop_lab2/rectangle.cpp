#include "rectangle.h"

// Конструктор без параметров
Rectangle::Rectangle() : Shape("blue", "Rectangle"), width(1.0), height(1.0) {
    std::cout << "Rectangle default constructor" << std::endl;
}

// Конструктор с параметрами
Rectangle::Rectangle(const std::string& color, double width, double height)
    : Shape(color, "Rectangle"), width(width), height(height) {
    std::cout << "Rectangle parameterized constructor, size: " << width << "x" << height << std::endl;
}

// Конструктор копирования
Rectangle::Rectangle(const Rectangle& other)
    : Shape(other), width(other.width), height(other.height) {
    std::cout << "Rectangle copy constructor, size: " << width << "x" << height << std::endl;
}

// Деструктор
Rectangle::~Rectangle() {
    std::cout << "Rectangle destructor: " << name << " size " << width << "x" << height << std::endl;
}

// Переопределенный метод рисования
void Rectangle::draw() const {
    std::cout << "Drawing rectangle: " << color << " rectangle " << width << "x" << height;
    std::cout << " (area: " << area() << ")" << std::endl;
}

// Переопределенный метод площади
double Rectangle::area() const {
    return width * height;
}

double Rectangle::getWidth() const {
    return width;
}

double Rectangle::getHeight() const {
    return height;
}

void Rectangle::setDimensions(double width, double height) {
    this->width = width;
    this->height = height;
}
