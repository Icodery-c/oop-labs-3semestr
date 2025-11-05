cmake_minimum_required(VERSION 3.10)
project(Lab5_OOP)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Разрешаем компиляцию в текущей директории
set(CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR})

# Создаем исполняемый файл из текущей директории
add_executable(lab5 main.cpp class.cpp)

# Включим все предупреждения
if(MSVC)
    target_compile_options(lab5 PRIVATE /W4)
else()
    target_compile_options(lab5 PRIVATE -Wall -Wextra -pedantic)
endif()
