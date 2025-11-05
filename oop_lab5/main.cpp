#include "class.h"

int main() {
    std::cout << "ЛАБОРАТОРНАЯ РАБОТА 5: Жизненный цикл объектов C++ и Виртуальность" << std::endl;
    std::cout << "================================================================" << std::endl;

    experiment1_virtual_vs_override();
    experiment2_type_checking();
    experiment3_parameter_passing();
    experiment4_object_return();
    experiment5_smart_pointers();
    demonstrate_problems();

    std::cout << "\nВсе эксперименты завершены!" << std::endl;
    return 0;
}
