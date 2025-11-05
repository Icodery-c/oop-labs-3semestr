#pragma once

#include <iostream>
#include <string>

class Point {
private:
    double x, y;
public:
    Point(double x = 0, double y = 0) : x(x), y(y) {
        std::cout << "Point constructor: (" << x << ", " << y << ")" << std::endl;
    }
    ~Point() {
        std::cout << "Point destructor: (" << x << ", " << y << ")" << std::endl;
    }
    double getX() const { return x; }
    double getY() const { return y; }
};

class Shape {
protected:
    std::string color;
    std::string name;

public:
    // Конструкторы
    Shape();  // без параметров
    Shape(const std::string& color, const std::string& name);  // с параметрами
    Shape(const Shape& other);  // копирования

    // Деструктор
    virtual ~Shape();

    // Методы
    virtual void draw() const;
    virtual double area() const;

    // Геттеры и сеттеры
    std::string getColor() const;
    std::string getName() const;
    void setColor(const std::string& color);
};
