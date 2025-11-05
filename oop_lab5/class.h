#pragma once

#include <iostream>
#include <string>
#include <memory>

// Базовый класс
class Base {
public:
    // Конструкторы и деструктор
    Base();
    Base(Base* obj);
    Base(Base& obj);
    virtual ~Base();

    // Методы
    virtual void method();
    void nonVirtualMethod();

    // Методы для проверки типа
    virtual std::string classname();
    virtual bool isA(const std::string& className);

    // Методы для демонстрации вызовов
    virtual void testMethod1();
    virtual void testMethod2();
};

// Производный класс
class Derived : public Base {
public:
    // Конструкторы и деструктор
    Derived();
    Derived(Derived* obj);
    Derived(Derived& obj);
    ~Derived();

    // Переопределенные методы
    void method() override;
    void nonVirtualMethod(); // Перекрытие, не переопределение

    // Методы для проверки типа
    std::string classname() override;
    bool isA(const std::string& className) override;
};

// Функции для экспериментов с передачей параметров
void func1(Base obj);
void func2(Base* obj);
void func3(Base& obj);

// Функции для экспериментов с возвратом объектов
Base func1_ret();
Base* func2_ret();
Base& func3_ret();
Base func4_ret();
Base* func5_ret();
Base& func6_ret();

// Функции экспериментов
void experiment1_virtual_vs_override();
void experiment2_type_checking();
void experiment3_parameter_passing();
void experiment4_object_return();
void experiment5_smart_pointers();
void demonstrate_problems();
