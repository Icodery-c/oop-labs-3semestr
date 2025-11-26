QT += core gui widgets
CONFIG += c++17
TEMPLATE = app
TARGET = lab4

SOURCES += \
    main.cpp \
    mainwindow.cpp \
    baseshape.cpp \
    circle.cpp \
    rectangle.cpp \
    triangle.cpp \
    line.cpp \
    shapestorage.cpp \
    shapewidget.cpp

HEADERS += \
    mainwindow.h \
    baseshape.h \
    circle.h \
    rectangle.h \
    triangle.h \
    line.h \
    shapestorage.h \
    shapewidget.h
