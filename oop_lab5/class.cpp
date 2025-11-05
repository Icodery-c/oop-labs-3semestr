#include "class.h"

// ==================== Base class implementation ====================

Base::Base() {
    std::cout << "Base constructor" << std::endl;
}

Base::Base(Base* obj) {
    std::cout << "Base copy constructor from pointer" << std::endl;
}

Base::Base(Base& obj) {
    std::cout << "Base copy constructor from reference" << std::endl;
}

Base::~Base() {
    std::cout << "Base destructor" << std::endl;
}

void Base::method() {
    std::cout << "Base method" << std::endl;
}

void Base::nonVirtualMethod() {
    std::cout << "Base non-virtual method" << std::endl;
}

std::string Base::classname() {
    return "Base";
}

bool Base::isA(const std::string& className) {
    return className == "Base";
}

void Base::testMethod1() {
    std::cout << "Base::testMethod1 calls: ";
    method(); // Виртуальный вызов
}

void Base::testMethod2() {
    std::cout << "Base::testMethod2 calls: ";
    nonVirtualMethod(); // Невиртуальный вызов
}

// ==================== Derived class implementation ====================

Derived::Derived() {
    std::cout << "Derived constructor" << std::endl;
}

Derived::Derived(Derived* obj) {
    std::cout << "Derived copy constructor from pointer" << std::endl;
}

Derived::Derived(Derived& obj) {
    std::cout << "Derived copy constructor from reference" << std::endl;
}

Derived::~Derived() {
    std::cout << "Derived destructor" << std::endl;
}

void Derived::method() {
    std::cout << "Derived method" << std::endl;
}

void Derived::nonVirtualMethod() {
    std::cout << "Derived non-virtual method" << std::endl;
}

std::string Derived::classname() {
    return "Derived";
}

bool Derived::isA(const std::string& className) {
    return className == "Derived" || Base::isA(className);
}

// ==================== Parameter passing functions ====================

void func1(Base obj) {
    std::cout << "func1(Base obj) - working with: " << obj.classname() << std::endl;
}

void func2(Base* obj) {
    std::cout << "func2(Base* obj) - working with: " << obj->classname() << std::endl;
}

void func3(Base& obj) {
    std::cout << "func3(Base& obj) - working with: " << obj.classname() << std::endl;
}

// ==================== Return object functions ====================

Base func1_ret() {
    Base localObj;
    std::cout << "func1_ret - returning local object by value" << std::endl;
    return localObj;
}

Base* func2_ret() {
    Base* localObj = new Base();
    std::cout << "func2_ret - returning dynamically allocated object by pointer" << std::endl;
    return localObj;
}

Base& func3_ret() {
    static Base staticObj;
    std::cout << "func3_ret - returning static object by reference" << std::endl;
    return staticObj;
}

Base func4_ret() {
    Base* obj = new Base();
    std::cout << "func4_ret - returning dynamically allocated object by value (PROBLEMATIC!)" << std::endl;
    return *obj;
}

Base* func5_ret() {
    Base localObj;
    std::cout << "func5_ret - returning pointer to local object (DANGEROUS!)" << std::endl;
    return &localObj;
}

Base& func6_ret() {
    Base localObj;
    std::cout << "func6_ret - returning reference to local object (DANGEROUS!)" << std::endl;
    return localObj;
}

// ==================== Experiment functions ====================

void experiment1_virtual_vs_override() {
    std::cout << "\n=== Эксперимент 1: Виртуальные vs перекрываемые методы ===" << std::endl;

    Base base;
    Derived derived;

    std::cout << "\n1. Прямой вызов:" << std::endl;
    base.method();
    derived.method();

    std::cout << "\n2. Через указатель на базовый класс:" << std::endl;
    Base* ptr1 = &base;
    Base* ptr2 = &derived;
    ptr1->method();
    ptr2->method();

    std::cout << "\n3. Невиртуальные методы:" << std::endl;
    ptr1->nonVirtualMethod();
    ptr2->nonVirtualMethod();

    std::cout << "\n4. Вызов из других методов:" << std::endl;
    std::cout << "Base object:" << std::endl;
    base.testMethod1();
    base.testMethod2();

    std::cout << "Derived object:" << std::endl;
    derived.testMethod1();
    derived.testMethod2();
}

void experiment2_type_checking() {
    std::cout << "\n=== Эксперимент 2: Проверка типов ===" << std::endl;

    Base* basePtr = new Base();
    Base* derivedPtr = new Derived();

    std::cout << "\n1. classname() method:" << std::endl;
    std::cout << "basePtr->classname(): " << basePtr->classname() << std::endl;
    std::cout << "derivedPtr->classname(): " << derivedPtr->classname() << std::endl;

    std::cout << "\n2. isA() method:" << std::endl;
    std::cout << "basePtr->isA('Base'): " << basePtr->isA("Base") << std::endl;
    std::cout << "basePtr->isA('Derived'): " << basePtr->isA("Derived") << std::endl;
    std::cout << "derivedPtr->isA('Base'): " << derivedPtr->isA("Base") << std::endl;
    std::cout << "derivedPtr->isA('Derived'): " << derivedPtr->isA("Derived") << std::endl;

    std::cout << "\n3. dynamic_cast:" << std::endl;
    Derived* cast1 = dynamic_cast<Derived*>(basePtr);
    Derived* cast2 = dynamic_cast<Derived*>(derivedPtr);

    std::cout << "dynamic_cast<Derived*>(basePtr): " << (cast1 ? "SUCCESS" : "FAILED") << std::endl;
    std::cout << "dynamic_cast<Derived*>(derivedPtr): " << (cast2 ? "SUCCESS" : "FAILED") << std::endl;

    std::cout << "\n4. Безопасное приведение с проверкой isA:" << std::endl;
    if (derivedPtr->isA("Derived")) {
        std::cout << "Safe to cast - object is Derived" << std::endl;
        Derived* safeCast = dynamic_cast<Derived*>(derivedPtr);
        if (safeCast) {
            safeCast->method();
        }
    }

    delete basePtr;
    delete derivedPtr;
}

void experiment3_parameter_passing() {
    std::cout << "\n=== Эксперимент 3: Передача параметров в функции ===" << std::endl;

    std::cout << "\n1. Передача объекта Base:" << std::endl;
    Base baseObj;
    std::cout << "Calling func1(baseObj):" << std::endl;
    func1(baseObj);
    std::cout << "Calling func2(&baseObj):" << std::endl;
    func2(&baseObj);
    std::cout << "Calling func3(baseObj):" << std::endl;
    func3(baseObj);

    std::cout << "\n2. Передача объекта Derived:" << std::endl;
    Derived derivedObj;
    std::cout << "Calling func1(derivedObj):" << std::endl;
    func1(derivedObj);
    std::cout << "Calling func2(&derivedObj):" << std::endl;
    func2(&derivedObj);
    std::cout << "Calling func3(derivedObj):" << std::endl;
    func3(derivedObj);
}

void experiment4_object_return() {
    std::cout << "\n=== Эксперимент 4: Возврат объектов из функций ===" << std::endl;

    std::cout << "\n1. Безопасные способы возврата:" << std::endl;
    std::cout << "func1_ret() - возврат по значению:" << std::endl;
    Base obj1 = func1_ret();
    std::cout << "func2_ret() - возврат указателя на динамический объект:" << std::endl;
    Base* obj2 = func2_ret();
    std::cout << "func3_ret() - возврат ссылки на статический объект:" << std::endl;
    Base& obj3 = func3_ret();

    std::cout << "\n2. Опасные способы возврата:" << std::endl;
    std::cout << "func4_ret() - утечка памяти:" << std::endl;
    Base obj4 = func4_ret();

    std::cout << "func5_ret() - висячий указатель:" << std::endl;
    Base* obj5 = func5_ret();

    std::cout << "func6_ret() - висячая ссылка:" << std::endl;
    Base& obj6 = func6_ret();

    // Очистка
    delete obj2;
}

void experiment5_smart_pointers() {
    std::cout << "\n=== Эксперимент 5: Умные указатели ===" << std::endl;

    std::cout << "\n1. unique_ptr - эксклюзивное владение:" << std::endl;
    {
        std::unique_ptr<Base> ptr1 = std::make_unique<Base>();
        std::cout << "ptr1 created, use count: 1 (implicit)" << std::endl;

        std::unique_ptr<Base> ptr2 = std::move(ptr1);
        std::cout << "After move: ptr1 is " << (ptr1 ? "valid" : "empty") << std::endl;
        std::cout << "After move: ptr2 is " << (ptr2 ? "valid" : "empty") << std::endl;

        std::unique_ptr<Base> ptr3 = std::make_unique<Derived>();
        std::cout << "Polymorphism with unique_ptr works!" << std::endl;
    }

    std::cout << "\n2. shared_ptr - разделяемое владение:" << std::endl;
    {
        std::shared_ptr<Base> ptr1 = std::make_shared<Derived>();
        std::cout << "ptr1 use count: " << ptr1.use_count() << std::endl;

        std::shared_ptr<Base> ptr2 = ptr1;
        std::cout << "After copy - ptr1 use count: " << ptr1.use_count() << std::endl;
        std::cout << "After copy - ptr2 use count: " << ptr2.use_count() << std::endl;

        {
            std::shared_ptr<Base> ptr3 = ptr1;
            std::cout << "In inner scope - use count: " << ptr1.use_count() << std::endl;
        }

        std::cout << "After inner scope - use count: " << ptr1.use_count() << std::endl;
    }

    std::cout << "\n3. Передача умных указателей в функции:" << std::endl;
    auto processObject = [](std::shared_ptr<Base> obj) {
        std::cout << "Processing object in function, use count: " << obj.use_count() << std::endl;
    };

    std::shared_ptr<Base> obj = std::make_shared<Derived>();
    std::cout << "Before function call, use count: " << obj.use_count() << std::endl;
    processObject(obj);
    std::cout << "After function call, use count: " << obj.use_count() << std::endl;
}

void demonstrate_problems() {
    std::cout << "\n=== ЯВНАЯ ДЕМОНСТРАЦИЯ ПРОБЛЕМ ===" << std::endl;

    // Проблема без виртуального деструктора
    std::cout << "1. ПРОБЛЕМА: Без виртуального деструктора:" << std::endl;
    class BadBase {
    public:
        ~BadBase() { std::cout << "BadBase destructor" << std::endl; }
    };

    class BadDerived : public BadBase {
    public:
        ~BadDerived() { std::cout << "BadDerived destructor" << std::endl; }
    };

    BadBase* badPtr = new BadDerived();
    delete badPtr;

    // Проблема срезки
    std::cout << "\n2. ПРОБЛЕМА: Срезка объекта:" << std::endl;
    Derived derived;
    Base sliced = derived;
    std::cout << "sliced.classname(): " << sliced.classname() << std::endl;
}
