QT += core gui widgets
CONFIG += c++17
TEMPLATE = app
TARGET = lab6

SOURCES += \
    main.cpp \
    mainwindow.cpp \
    baseshape.cpp \
    circle.cpp \
    rectangle.cpp \
    triangle.cpp \
    group.cpp \
    line.cpp \
    shapestorage.cpp \
    shapewidget.cpp \
    shapefactory.cpp  # ← ДОБАВЛЯЕМ

HEADERS += \
    mainwindow.h \
    baseshape.h \
    circle.h \
    rectangle.h \
    triangle.h \
    group.h \
    line.h \
    shapestorage.h \
    shapewidget.h \
    shapefactory.h  # ← ДОБАВЛЯЕМ
