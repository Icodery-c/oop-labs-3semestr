#pragma once

#include <memory>
#include "baseshape.h"

class ShapeFactory
{
public:
    virtual ~ShapeFactory() = default;

    // Создание фигуры по типу
    virtual std::unique_ptr<BaseShape> createShape(const QString& type) = 0;

    // Загрузка фигуры из потока
    virtual std::unique_ptr<BaseShape> loadShape(QTextStream& stream) = 0;
};

class TextShapeFactory : public ShapeFactory
{
public:
    std::unique_ptr<BaseShape> createShape(const QString& type) override;
    std::unique_ptr<BaseShape> loadShape(QTextStream& stream) override;
};
