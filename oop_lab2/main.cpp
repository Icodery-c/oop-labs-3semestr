#include <iostream>
#include <string>
#include "shape.h"
#include "circle.h"
#include "rectangle.h"

// Функция для демонстрации создания объектов
void demonstrateObjectCreation() {
    std::cout << "\n=== 1. Демонстрация создания объектов ===" << std::endl;

    std::cout << "\n--- Статическое создание ---" << std::endl;
    Shape shape1;  // конструктор без параметров
    Shape shape2("green", "Generic Shape");  // конструктор с параметрами

    std::cout << "\n--- Динамическое создание ---" << std::endl;
    Shape* shape3 = new Shape("yellow", "Dynamic Shape");

    std::cout << "\n--- Конструктор копирования ---" << std::endl;
    Shape shape4 = shape2;  // копирование

    // Вызов методов
    shape1.draw();
    shape2.draw();
    shape3->draw();
    shape4.draw();

    // Очистка динамической памяти
    delete shape3;
}

// Функция для демонстрации наследования
void demonstrateInheritance() {
    std::cout << "\n=== 2. Демонстрация наследования ===" << std::endl;

    std::cout << "\n--- Создание Circle ---" << std::endl;
    Circle circle1;  // конструктор без параметров
    Circle circle2("purple", 2.5);  // конструктор с параметрами

    std::cout << "\n--- Создание Rectangle ---" << std::endl;
    Rectangle rect1;
    Rectangle rect2("orange", 3.0, 4.0);

    // Вызов методов
    circle1.draw();
    circle2.draw();
    rect1.draw();
    rect2.draw();

    std::cout << "\n--- Копирование объектов-наследников ---" << std::endl;
    Circle circle3 = circle2;  // конструктор копирования
    circle3.draw();
}

// Функция для демонстрации работы с указателями
void demonstratePointers() {
    std::cout << "\n=== 3. Демонстрация работы с указателями ===" << std::endl;

    std::cout << "\n--- Указатели базового класса на объекты наследников ---" << std::endl;
    Shape* shapePtr1 = new Circle("pink", 3.0);
    Shape* shapePtr2 = new Rectangle("brown", 2.0, 5.0);

    // Вызов виртуальных методов
    shapePtr1->draw();  // вызовет Circle::draw()
    shapePtr2->draw();  // вызовет Rectangle::draw()

    // Вызов невиртуальных методов
    std::cout << "Shape1 color: " << shapePtr1->getColor() << std::endl;
    std::cout << "Shape2 color: " << shapePtr2->getColor() << std::endl;

    // Очистка
    delete shapePtr1;
    delete shapePtr2;
}

// Circle с прямой композицией Point
class CircleWithPoint : public Shape {
private:
    double radius;
    Point center;  // Прямой объект (не указатель!)

public:
    // Конструктор с инициализацией в списке
    CircleWithPoint(const std::string& color, double radius, double x, double y)
        : Shape(color, "CircleWithPoint"), radius(radius), center(x, y) {
        std::cout << "CircleWithPoint constructor complete" << std::endl;
    }

    ~CircleWithPoint() {
        std::cout << "CircleWithPoint destructor" << std::endl;
    }

    void draw() const override {
        std::cout << "CircleWithPoint: " << color << " at ("
                  << center.getX() << ", " << center.getY()
                  << ") radius " << radius << std::endl;
    }
};

// Класс с композицией через указатель
class ShapeWithPointer {
private:
    Shape* shapePtr;
    std::string containerName;

public:
    ShapeWithPointer(const std::string& name, Shape* shape)
        : containerName(name), shapePtr(shape) {
        std::cout << "ShapeWithPointer constructor: " << name << std::endl;
    }

    ~ShapeWithPointer() {
        std::cout << "ShapeWithPointer destructor: " << containerName << std::endl;
        delete shapePtr;
    }

    void display() const {
        std::cout << "Pointer container '" << containerName << "' contains: ";
        shapePtr->draw();
    }
};

void demonstrateCompositionDifference() {
    std::cout << "\n=== Демонстрация РАЗНИЦЫ композиции ===" << std::endl;

    std::cout << "\n--- 1. Композиция с ПРЯМЫМ объектом ---" << std::endl;
    {
        CircleWithPoint circle("red", 2.0, 10.0, 20.0);
        circle.draw();
    } // Point уничтожится автоматически!

    std::cout << "\n--- 2. Композиция с УКАЗАТЕЛЕМ ---" << std::endl;
    {
        ShapeWithPointer container("PointerComp", new Circle("blue", 3.0));
        container.display();
    } // Нужно самим delete в деструкторе!
}

// Дополнительные демонстрации
void demonstrateAdvancedConcepts() {
    std::cout << "\n=== 5. Дополнительные демонстрации ===" << std::endl;

    std::cout << "\n--- Массив указателей на базовый класс ---" << std::endl;
    Shape* shapes[3];
    shapes[0] = new Circle("red", 1.0);
    shapes[1] = new Rectangle("blue", 2.0, 3.0);
    shapes[2] = new Circle("green", 1.5);

    for (int i = 0; i < 3; ++i) {
        shapes[i]->draw();
        std::cout << "Area: " << shapes[i]->area() << std::endl;
    }

    // Очистка
    for (int i = 0; i < 3; ++i) {
        delete shapes[i];
    }

    std::cout << "\n--- Демонстрация присваивания ---" << std::endl;
    Circle circle1("yellow", 2.0);
    Circle circle2("black", 1.0);

    std::cout << "Before assignment:" << std::endl;
    circle1.draw();
    circle2.draw();

    circle2 = circle1;  // присваивание

    std::cout << "After assignment:" << std::endl;
    circle1.draw();
    circle2.draw();

    circle2.setRadius(3.0);  // изменяем только circle2

    std::cout << "After modifying circle2:" << std::endl;
    circle1.draw();
    circle2.draw();
}

int main() {
    std::cout << "=== Лабораторная работа 2: Объекты и Классы ===" << std::endl;

    demonstrateObjectCreation();
    demonstrateInheritance();
    demonstratePointers();
    demonstrateCompositionDifference();
    demonstrateAdvancedConcepts();

    std::cout << "\n=== Завершение программы ===" << std::endl;
    std::cout << "Все автоматические объекты будут уничтожены..." << std::endl;

    return 0;
}
